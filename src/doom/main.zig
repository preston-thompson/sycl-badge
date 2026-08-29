const std = @import("std");
const microzig = @import("microzig");
const board = microzig.board;

const audio = @import("../os/drivers/audio.zig");
const gpio = @import("../os/drivers/gpio.zig");
const init = @import("../os/system/init.zig");
const interrupts = @import("../os/interrupts.zig");
const lcd = @import("../os/drivers/lcd.zig");
const timer = @import("../os/drivers/timer.zig");

extern fn sycl_doom_main() c_int;

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
    while (lcd.isBusy()) {}

    doomStatus("enter doom");
    _ = sycl_doom_main();
    doomStatus("doom returned");

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

fn doomStatus(message: []const u8) void {
    lcd.clearScreen(lcd.BLACK);
    while (lcd.isBusy()) {}
    lcd.drawString(0, 0, "DOOM STATUS", lcd.CYAN, lcd.BLACK, 1);
    lcd.drawString(0, 16, message, lcd.WHITE, lcd.BLACK, 1);
    while (lcd.isBusy()) {}
}

export fn sycl_doom_status(message: [*:0]const u8) void {
    doomStatus(std.mem.sliceTo(message, 0));
}

export fn sycl_doom_micros() u64 {
    return timer.micros();
}

export fn sycl_doom_present_rgb565(buffer: [*]const u16, width: u32, height: u32) void {
    if (width == lcd.width and height == lcd.height) {
        lcd.writeBuffer(0, 0, lcd.width, lcd.height, buffer[0 .. lcd.width * lcd.height]);
        return;
    }

    const copy_width: u32 = @min(width, lcd.width);
    const copy_height: u32 = @min(height, lcd.height);
    const src_x: u32 = if (width > copy_width) (width - copy_width) / 2 else 0;
    const src_y: u32 = if (height > copy_height) (height - copy_height) / 2 else 0;
    const dst_x: u16 = @intCast((lcd.width - copy_width) / 2);
    const dst_y: u16 = @intCast((lcd.height - copy_height) / 2);

    var y: u32 = 0;
    while (y < copy_height) : (y += 1) {
        const row_start = (src_y + y) * width + src_x;
        lcd.writeBuffer(dst_x, @intCast(dst_y + y), @intCast(copy_width), 1, buffer[row_start .. row_start + copy_width]);
        while (lcd.isBusy()) {}
    }
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

export fn sycl_doom_error(message: [*:0]const u8) void {
    const text = std.mem.sliceTo(message, 0);
    lcd.clearScreen(lcd.BLACK);
    while (lcd.isBusy()) {}
    lcd.drawString(0, 0, "DOOM ERROR", lcd.RED, lcd.BLACK, 1);
    lcd.drawString(0, 16, text[0..@min(text.len, 20)], lcd.WHITE, lcd.BLACK, 1);
    if (text.len > 20) {
        lcd.drawString(0, 28, text[20..@min(text.len, 40)], lcd.WHITE, lcd.BLACK, 1);
    }
    if (text.len > 40) {
        lcd.drawString(0, 40, text[40..@min(text.len, 60)], lcd.WHITE, lcd.BLACK, 1);
    }
    while (lcd.isBusy()) {}
}

comptime {
    _ = std;
}
