# fract-ol

A high-performance fractal visualization application written in C that renders real-time interactive fractals using the MiniLibX graphics library. Explore infinite mathematical beauty with smooth zooming, panning, and customizable rendering parameters.

## Overview

fract-ol is a graphical exploration tool for three of the most famous fractals in mathematics:
- **Mandelbrot Set** - The quintessential fractal defined by the iteration of z → z² + c
- **Julia Set** - A family of fractals parametrized by complex numbers
- **Burning Ship** - A variant of Mandelbrot with absolute value transformations

The application provides an intuitive interface for exploring these fractals with full interactive control over zoom levels, pan coordinates, and rendering parameters.

## Features

### Core Functionality
- **Three Fractal Engines**: Complete implementations of Mandelbrot, Julia, and Burning Ship fractals
- **Real-time Rendering**: Event-driven architecture for smooth, responsive interaction
- **Adaptive Zooming**: Smooth zoom centered at mouse position with configurable zoom factor (1.1×)
- **Pan Navigation**: Arrow key controls for exploring different regions of the complex plane
- **Color Palette System**: 16-color palette mapping iteration depths to visual gradients

### Graphics & Performance
- **800×600 Resolution**: Fixed viewport optimized for detailed fractal exploration
- **Iteration Depth**: Configurable maximum iterations (default 200) balancing quality and speed
- **Direct Pixel Manipulation**: Optimized pixel buffer access for fast rendering
- **Hardware-Accelerated Display**: Uses X11 server-side rendering via MiniLibX

## System Requirements

### Dependencies
- **GCC**: C compiler with C99 support
- **X11 Development Libraries**: libx11-dev, libxext-dev
- **BSD Library**: libbsd-dev (for compatibility functions)
- **MiniLibX**: Included as submodule (builds automatically)

### Supported Platforms
- Linux (native or WSL2)
- Any system with X11 server support

## Installation

### Prerequisites (Ubuntu/Debian/WSL)
```bash
sudo apt-get update
sudo apt-get install -y gcc make libbsd-dev libx11-dev libxext-dev
```

### Build
```bash
make              # Build the executable
make clean        # Remove object files
make fclean       # Remove all build artifacts
make re           # Clean rebuild
```

## Usage

### Launching the Application

**Mandelbrot Set:**
```bash
./fractol mandelbrot
```

**Julia Set** (requires two complex parameters):
```bash
./fractol julia <real_part> <imaginary_part>
```

Examples:
```bash
./fractol julia -0.7 0.27015      # Classic Julia spiral
./fractol julia -0.8 0.156        # Intricate filament pattern
./fractol julia 0.285 0.01        # Seahorse valley
```

**Burning Ship:**
```bash
./fractol burning_ship
```

### Interactive Controls

| Control | Action |
|---------|--------|
| **Mouse Scroll Up** | Zoom in (1.1× magnification) |
| **Mouse Scroll Down** | Zoom out |
| **Arrow Keys** | Pan the view (translate by 0.1 units) |
| **ESC / Window Close** | Exit application |

## Technical Architecture

### Core Components

**Rendering Engine** (`render.c`, `render_utils.c`)
- Main loop iterates through all pixels (800×600)
- Per-fractal mathematical computation (Mandelbrot, Julia, Burning Ship)
- Iteration-based color mapping with smooth gradients
- Direct write to pixel buffer for maximum speed

**Event System** (`events.c`)
- Mouse hooks for zoom operations centered at cursor position
- Keyboard hooks for ESC key and arrow navigation
- Window close event handling with proper resource cleanup

**Memory Management**
- Centralized allocation in `mem_alloc()`
- Proper cleanup and deallocation in `clean_exit()`
- No memory leaks in event-driven loop

**Coordinate Mapping**
- Screen-to-complex-plane transformation using linear interpolation
- Dynamic range mapping based on zoom and offset parameters
- Per-pixel coordinate calculation for mathematical accuracy

### Data Structures

```c
typedef struct s_mlx {
    t_type      type;          // MANDELBROT, JULIA, or BURNING_SHIP
    void        *mlx;          // MiniLibX connection
    void        *win;          // Window pointer
    t_image     img;           // Pixel buffer and metadata
    double      zoom;          // Current zoom level
    double      offset_x;      // Horizontal translation
    double      offset_y;      // Vertical translation
    int         palette[16];   // Color lookup table
    t_fractal   fractal;       // Complex number state
} t_mlx;
```

### Mathematical Algorithms

**Mandelbrot Iteration:**
z(n+1) = z(n)² + c where c is the pixel coordinate in the complex plane.

**Julia Iteration:**
z(n+1) = z(n)² + c where c is a fixed complex parameter and z is the pixel coordinate.

**Burning Ship Iteration:**
z(n+1) = (|Re(z(n))| + i|Im(z(n)|)² + c

Iteration continues until |z(n)| > 2 or maximum iterations reached. Iteration count determines final pixel color.

## Build Configuration

### Compiler Flags
```
-Wall -Wextra -Werror
```
Strict compilation with all warnings enabled and treated as errors ensures code quality.

### Constants
- **WIDTH**: 800 pixels
- **HEIGHT**: 600 pixels
- **MAX_ITER**: 200 iterations
- **ZOOM_FACTOR**: 1.1 (10% magnification per scroll)
- **PALETTE_SIZE**: 16 colors

## Project Structure

```
fract-ol/
├── main.c              # Application entry point, initialization
├── fractol.h           # Header with structures, constants, declarations
├── events.c            # Event handlers (keyboard, mouse, window)
├── render.c            # Core fractal rendering loop
├── render_utils.c      # Rendering helpers (color mapping, math)
├── render_utils_1.c    # Additional rendering utilities
├── mlx_utils.c         # MiniLibX wrapper functions
├── utils.c             # General utilities (string parsing, validation)
├── utils_1.c           # Additional utilities
├── Makefile            # Build configuration
└── minilibx-linux/     # MiniLibX graphics library (submodule)
```

## Performance Considerations

- **Iteration Limit**: 200 iterations balances visual detail with render speed
- **Resolution**: 800×600 provides responsive 60+ FPS rendering on modern hardware
- **Zoom Range**: Practical zoom limited by floating-point precision
- **Real-time Responsiveness**: Event-driven architecture eliminates unnecessary recomputation

## Development Notes

### Building on WSL
The application works perfectly under WSL2 with X11 server support. Ensure your WSL distribution has X11 forwarding configured.

### Input Validation
- Julia set parameters validated as floating-point numbers
- Fractal type checked against supported options
- Proper error messages for invalid inputs

### Color Palette
The 16-color palette is dynamically initialized and smoothly interpolates between colors based on iteration count, creating visually appealing gradients.

## Author

**modat** (modat@student.42.fr)

Created as part of the 42 School curriculum.

## License

Educational use. See LICENSE file for details.

## Troubleshooting

### Build Errors

**"cannot find -lbsd"**
```bash
sudo apt-get install -y libbsd-dev
```

**Missing X11 libraries**
```bash
sudo apt-get install -y libx11-dev libxext-dev
```

### Runtime Issues

**Window doesn't render**
- Verify X11 server is running
- On WSL: Ensure X11 forwarding is configured
- Check that MiniLibX compiled successfully

**Fractals appear incorrect or missing**
- Verify correct fractal type name (mandelbrot, julia, burning_ship)
- For Julia: check that parameters are valid floating-point numbers
- Ensure zoom level is within floating-point precision limits

## References

- [Mandelbrot Set](https://en.wikipedia.org/wiki/Mandelbrot_set)
- [Julia Set](https://en.wikipedia.org/wiki/Julia_set)
- [Burning Ship Fractal](https://en.wikipedia.org/wiki/Burning_Ship_fractal)
- [MiniLibX Documentation](https://github.com/42Paris/minilibx-linux)
