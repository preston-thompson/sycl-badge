const std = @import("std");
const microzig = @import("microzig");
const board = microzig.board;

const audio = @import("../os/drivers/audio.zig");
const gpio = @import("../os/drivers/gpio.zig");
const init = @import("../os/system/init.zig");
const interrupts = @import("../os/interrupts.zig");
const lcd = @import("../os/drivers/lcd.zig");
const timer = @import("../os/drivers/timer.zig");

pub const panic = @import("../os/system/panic.zig").panic;

pub const microzig_options: microzig.Options = .{
    .interrupts = interrupts.interrupts,
};

pub fn main() !void {
    try init.init(.{
        .lcd_pins = lcd.createDT018BTFTPins(),
        .lcd_config = lcd.createDT018BTFTConfig(),
        .init_core1 = false,
    });

    lcd.clearScreen(lcd.BLACK);
    while (lcd.isBusy()) {}

    lcd.drawString(20, 28, "SYCL DOOM", lcd.RED, lcd.BLACK, 2);
    lcd.drawString(16, 54, "firmware scaffold", lcd.WHITE, lcd.BLACK, 1);
    lcd.drawString(20, 74, "GBADoom next", lcd.CYAN, lcd.BLACK, 1);

    var led_deadline = timer.micros() + 250_000;
    while (true) {
        audio.poll();
        lcd.poll();

        const now = timer.micros();
        if (now >= led_deadline) {
            led_deadline = now + 250_000;
            gpio.toggle(board.led_pin);
        }
    }
}

comptime {
    _ = std;
}
