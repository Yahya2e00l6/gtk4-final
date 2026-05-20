# GTK4 Application

## Build

```bash
make        # Build
make debug  # Debug build with symbols
make clean  # Clean build
```

## Run & Debug

- **Run**: `make run` or run via `./build/gtk-app`
- **Debug**: Press F5 or use Run menu > start debugging

## XML Demo

- Build and run default XML: `make xml-demo`
- Run a specific XML file: `make xml-demo XML=examples/xml/demo_forms.xml`
- Direct binary usage: `./build/xml-demo examples/xml/demo_dashboard.xml`

Available XML examples:
- `examples/xml/demo_app.xml`
- `examples/xml/demo_forms.xml`
- `examples/xml/demo_dashboard.xml`
- `examples/xml/demo_gallery.xml`
- `examples/xml/assignment_ui_short.xml`
- `examples/xml/layout_stress.xml`

Wrapper C API examples:
- Assignment UI: `make assignment-api`
- Layout stress UI: `make layout-stress-api`

## Technical Reports (LaTeX)

The project includes two technical reports documented in French.

- **Volume 1 (Architecture & Interface)**: Documents the wrapper configuration structs and usage.
  - Build: `make -C report`
  - Output: `report/build/main.pdf`
- **Volume 2 (Implementation)**: Documents the internal logic and GTK4/GLib API mappings.
  - Build: `make -C report2`
  - Output: `report2/build/main.pdf`

Note: Building reports requires a LaTeX distribution (e.g., TeX Live) with `latexmk` and `pdflatex`.
