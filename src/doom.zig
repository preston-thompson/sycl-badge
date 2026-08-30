const std = @import("std");
const microzig = @import("microzig");
const board = microzig.board;

const init = @import("os/system/init.zig");
const interrupts = @import("os/interrupts.zig");
const lcd = @import("os/drivers/lcd.zig");
const timer = @import("os/drivers/timer.zig");

pub const panic = @import("os/system/panic.zig").panic;

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

    while (true) {
        lcd.poll();
    }
}

comptime {
    _ = std;
}
