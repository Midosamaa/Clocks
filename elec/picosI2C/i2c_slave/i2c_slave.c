#include <i2c_slave.h>
#include <hardware/irq.h>

typedef struct i2c_slave_t
{
    i2c_inst_t *i2c;
    i2c_slave_handler_t handler;
    bool transfer_in_progress;
} i2c_slave_t;

static i2c_slave_t i2c_slaves[2];

static inline void finish_transfer(i2c_slave_t *slave) {
    if (slave->transfer_in_progress) {
        slave->handler(slave->i2c, I2C_SLAVE_FINISH);
        slave->transfer_in_progress = false;
    }
}

static void __not_in_flash_func(i2c_slave_irq_handler)(i2c_slave_t *slave) {
    i2c_inst_t *i2c = slave->i2c;
    i2c_hw_t *hw = i2c_get_hw(i2c);

    uint32_t intr_stat = hw->intr_stat;
    if (intr_stat == 0) {
        return;
    }
    if (intr_stat & I2C_IC_INTR_STAT_R_TX_ABRT_BITS) {
        hw->clr_tx_abrt;
        finish_transfer(slave);
    }
    if (intr_stat & I2C_IC_INTR_STAT_R_START_DET_BITS) {
        hw->clr_start_det;
        finish_transfer(slave);
    }
    if (intr_stat & I2C_IC_INTR_STAT_R_STOP_DET_BITS) {
        hw->clr_stop_det;
        finish_transfer(slave);
    }
    if (intr_stat & I2C_IC_INTR_STAT_R_RX_FULL_BITS) {
        slave->transfer_in_progress = true;
        slave->handler(i2c, I2C_SLAVE_RECEIVE);
    }
    if (intr_stat & I2C_IC_INTR_STAT_R_RD_REQ_BITS) {
        hw->clr_rd_req;
        slave->transfer_in_progress = true;
        slave->handler(i2c, I2C_SLAVE_REQUEST);
    }
}

static void __not_in_flash_func(i2c0_slave_irq_handler)() {
    i2c_slave_irq_handler(&i2c_slaves[0]);
}

static void __not_in_flash_func(i2c1_slave_irq_handler)() {
    i2c_slave_irq_handler(&i2c_slaves[1]);
}

void i2c_slave_init(i2c_inst_t *i2c, uint8_t address, i2c_slave_handler_t handler) {
    assert(i2c == i2c0 || i2c == i2c1);
    assert(handler != NULL);

    uint i2c_index = i2c_hw_index(i2c);
    i2c_slave_t *slave = &i2c_slaves[i2c_index];
    slave->i2c = i2c;
    slave->handler = handler;

    // Note: The I2C slave does clock stretching implicitly after a RD_REQ, while the Tx FIFO is empty.
    // There is also an option to enable clock stretching while the Rx FIFO is full, but we leave it
    // disabled since the Rx FIFO should never fill up (unless slave->handler() is way too slow).
    i2c_set_slave_mode(i2c, true, address);

    i2c_hw_t *hw = i2c_get_hw(i2c);
    // unmask necessary interrupts
    hw->intr_mask = I2C_IC_INTR_MASK_M_RX_FULL_BITS | I2C_IC_INTR_MASK_M_RD_REQ_BITS | I2C_IC_RAW_INTR_STAT_TX_ABRT_BITS | I2C_IC_INTR_MASK_M_STOP_DET_BITS | I2C_IC_INTR_MASK_M_START_DET_BITS;

    // enable interrupt for current core
    uint num = I2C0_IRQ + i2c_index;
    irq_set_exclusive_handler(num, i2c_index == 0 ? i2c0_slave_irq_handler : i2c1_slave_irq_handler);
    irq_set_enabled(num, true);
}

void i2c_slave_deinit(i2c_inst_t *i2c) {
    assert(i2c == i2c0 || i2c == i2c1);

    uint i2c_index = i2c_hw_index(i2c);
    i2c_slave_t *slave = &i2c_slaves[i2c_index];
    assert(slave->i2c == i2c); // should be called after i2c_slave_init()

    slave->i2c = NULL;
    slave->handler = NULL;
    slave->transfer_in_progress = false;

    uint num = I2C0_IRQ + i2c_index;
    irq_set_enabled(num, false);
    irq_remove_handler(num, i2c_index == 0 ? i2c0_slave_irq_handler : i2c1_slave_irq_handler);

    i2c_hw_t *hw = i2c_get_hw(i2c);
    hw->intr_mask = I2C_IC_INTR_MASK_RESET;

    i2c_set_slave_mode(i2c, false, 0);
}
