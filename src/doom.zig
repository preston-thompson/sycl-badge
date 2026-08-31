const microzig = @import("microzig");
const board = microzig.board;

const init = @import("os/system/init.zig");
const gpio = @import("os/drivers/gpio.zig");
const interrupts = @import("os/interrupts.zig");
const lcd = @import("os/drivers/lcd.zig");
const timer = @import("os/drivers/timer.zig");
const std = @import("std");

pub const panic = @import("os/system/panic.zig").panic;

export fn sycl_doom_status(message_ptr: [*:0]const u8) void {
    const message = std.mem.sliceTo(message_ptr, 0);
    lcd.clearScreen(lcd.BLACK);
    while (lcd.isBusy()) {}
    
    lcd.drawString(10, 20, "DOOM STATUS:", lcd.CYAN, lcd.BLACK, 1);
    lcd.drawString(10, 40, message, lcd.WHITE, lcd.BLACK, 1);
    while (lcd.isBusy()) {}
}

extern fn sycl_doom_main() c_int;

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
    while (lcd.isBusy()) {}

    _ = sycl_doom_main();
}

export fn sycl_doom_micros() u64 {
    return timer.micros();
}

export fn sycl_doom_present(buffer: [*]const u16) void {
    lcd.writeBuffer(0, 0, lcd.width, lcd.height, buffer[0 .. lcd.width * lcd.height]);
}

export fn sycl_doom_buttons() u32 {
    var buttons: u32 = 0;
    if (gpio.isButtonPressed(board.button_start)) buttons |= 1 << 0;
    if (gpio.isButtonPressed(board.button_select)) buttons |= 1 << 1;
    if (gpio.isButtonPressed(board.button_a)) buttons |= 1 << 2;
    if (gpio.isButtonPressed(board.button_b)) buttons |= 1 << 3;
    if (gpio.isButtonPressed(board.joystick_up)) buttons |= 1 << 4;
    if (gpio.isButtonPressed(board.joystick_down)) buttons |= 1 << 5;
    if (gpio.isButtonPressed(board.joystick_left)) buttons |= 1 << 6;
    if (gpio.isButtonPressed(board.joystick_right)) buttons |= 1 << 7;
    if (gpio.isButtonPressed(board.joystick_click)) buttons |= 1 << 8;
    return buttons;
}
