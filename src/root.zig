pub const doom = @import("doom/main.zig");
pub const main = doom.main;
pub const panic = doom.panic;
pub const microzig_options = doom.microzig_options;

pub const os = struct {
    pub const audio = @import("os/drivers/audio.zig");
    pub const gpio = @import("os/drivers/gpio.zig");
    pub const init = @import("os/system/init.zig");
    pub const interrupts = @import("os/interrupts.zig");
    pub const lcd = @import("os/drivers/lcd.zig");
    pub const panic = @import("os/system/panic.zig");
    pub const timer = @import("os/drivers/timer.zig");
};
