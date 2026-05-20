#include "widgets/button.h"
#include "widgets/container.h"
#include "widgets/display.h"
#include "widgets/input.h"
#include "widgets/theme.h"
#include "widgets/toggle.h"
#include "widgets/window.h"

static GtkWidget *section_title(const char *text) {
    return create_label(&(label_config){
        .text = text,
        .style = {.css_class = "title-2", .set_halign = true, .halign = GTK_ALIGN_START},
    });
}

static GtkWidget *make_far_edges_section(void) {
    GtkWidget *grid = create_grid(&(grid_config){
        .column_spacing = 12,
        .row_spacing = 8,
        .style = {.set_hexpand = true, .hexpand = true},
    });

    container_add(grid, create_button(&(button_config){
        .label = "LEFT",
        .style = {.width_request = 140},
    }), 0, 0, 1, 1);

    container_add(grid, create_label(&(label_config){
        .text = "CENTER",
        .style = {.set_halign = true, .halign = GTK_ALIGN_CENTER, .set_hexpand = true, .hexpand = true},
    }), 1, 0, 1, 1);

    container_add(grid, create_button(&(button_config){
        .label = "RIGHT",
        .style = {.width_request = 140, .set_halign = true, .halign = GTK_ALIGN_END},
    }), 2, 0, 1, 1);

    return grid;
}

static GtkWidget *make_random_grid_section(void) {
    GtkWidget *grid = create_grid(&(grid_config){
        .column_spacing = 10,
        .row_spacing = 10,
        .style = {.set_hexpand = true, .hexpand = true},
    });

    container_add(grid, create_button(&(button_config){.label = "0,0", .style = {.width_request = 90}}), 0, 0, 1, 1);
    container_add(grid, create_button(&(button_config){.label = "4,0", .style = {.width_request = 90}}), 4, 0, 1, 1);
    container_add(grid, create_label(&(label_config){
        .text = "spans 3 cols",
        .style = {.css_class = "title-2", .set_halign = true, .halign = GTK_ALIGN_CENTER},
    }), 1, 1, 3, 1);
    container_add(grid, create_entry(&(entry_config){
        .placeholder = "wide entry at row 2",
        .style = {.width_request = 420},
    }), 0, 2, 4, 1);
    container_add(grid, create_button(&(button_config){.label = "tiny", .style = {.width_request = 70}}), 4, 2, 1, 1);
    container_add(grid, create_checkbox(&(checkbox_config){.label = "lower-left"}), 0, 4, 1, 1);

    GtkWidget *first = create_radio_button(&(radio_button_config){.label = "A"});
    container_add(grid, first, 2, 4, 1, 1);
    container_add(grid, create_radio_button(&(radio_button_config){.label = "B", .group_with = first, .is_active = true}), 3, 4, 1, 1);
    container_add(grid, create_radio_button(&(radio_button_config){.label = "C", .group_with = first}), 4, 4, 1, 1);

    return grid;
}

static GtkWidget *make_margin_section(void) {
    GtkWidget *box = create_box(&(box_config){.orientation = GTK_ORIENTATION_VERTICAL, .spacing = 8});

    container_add(box, create_button(&(button_config){
        .label = "normal start",
        .style = {.width_request = 180, .set_halign = true, .halign = GTK_ALIGN_START},
    }), 0, 0, 0, 0);
    container_add(box, create_button(&(button_config){
        .label = "pushed right by margin_start=220",
        .style = {.width_request = 300, .margin_start = 220, .set_halign = true, .halign = GTK_ALIGN_START},
    }), 0, 0, 0, 0);
    container_add(box, create_button(&(button_config){
        .label = "aligned end",
        .style = {.width_request = 180, .set_halign = true, .halign = GTK_ALIGN_END},
    }), 0, 0, 0, 0);
    container_add(box, create_button(&(button_config){
        .label = "center + top margin",
        .style = {.width_request = 220, .margin_top = 18, .set_halign = true, .halign = GTK_ALIGN_CENTER},
    }), 0, 0, 0, 0);

    return box;
}

static GtkWidget *make_form_section(void) {
    static const char *choices[] = {"First", "Second", "Third", NULL};
    GtkWidget *grid = create_grid(&(grid_config){
        .column_spacing = 12,
        .row_spacing = 10,
        .style = {.set_halign = true, .halign = GTK_ALIGN_START},
    });

    container_add(grid, create_label(&(label_config){.text = "Name"}), 0, 0, 1, 1);
    container_add(grid, create_entry(&(entry_config){.placeholder = "left field", .style = {.width_request = 220}}), 1, 0, 1, 1);
    container_add(grid, create_label(&(label_config){.text = "Score"}), 3, 0, 1, 1);
    container_add(grid, create_spin_button(&(spin_button_config){.min_value = 0, .max_value = 20, .step = 1, .value = 12, .style = {.width_request = 90}}), 4, 0, 1, 1);

    container_add(grid, create_label(&(label_config){.text = "Choice"}), 0, 1, 1, 1);
    container_add(grid, create_dropdown(&(dropdown_config){.options = choices, .style = {.width_request = 220}}), 1, 1, 1, 1);
    container_add(grid, create_button(&(button_config){.label = "Submit on far col", .style = {.width_request = 160}}), 4, 1, 1, 1);

    return grid;
}

static GtkWidget *build_layout_stress(void) {
    GtkWidget *root = create_box(&(box_config){
        .orientation = GTK_ORIENTATION_VERTICAL,
        .spacing = 18,
        .style = {.margin_top = 16, .margin_bottom = 16, .margin_start = 16, .margin_end = 16, .set_hexpand = true, .hexpand = true, .set_vexpand = true, .vexpand = true},
    });

    container_add(root, section_title("1) Same row: far left, centered, far right"), 0, 0, 0, 0);
    container_add(root, make_far_edges_section(), 0, 0, 0, 0);
    container_add(root, section_title("2) Random grid positions and spans"), 0, 0, 0, 0);
    container_add(root, make_random_grid_section(), 0, 0, 0, 0);
    container_add(root, section_title("3) Margins: push individual widgets around"), 0, 0, 0, 0);
    container_add(root, make_margin_section(), 0, 0, 0, 0);
    container_add(root, section_title("4) Mixed form: labels left, fields right"), 0, 0, 0, 0);
    container_add(root, make_form_section(), 0, 0, 0, 0);

    GtkWidget *buttons = create_box(&(box_config){
        .orientation = GTK_ORIENTATION_HORIZONTAL,
        .spacing = 32,
        .style = {.margin_top = 16, .set_halign = true, .halign = GTK_ALIGN_CENTER},
    });
    container_add(buttons, create_button(&(button_config){.label = "OK", .icon_name = "emblem-ok-symbolic", .style = {.width_request = 180, .height_request = 50}}), 0, 0, 0, 0);
    container_add(buttons, create_button(&(button_config){.label = "Cancel", .icon_name = "window-close-symbolic", .style = {.width_request = 180, .height_request = 50}}), 0, 0, 0, 0);
    container_add(root, buttons, 0, 0, 0, 0);

    return root;
}

static void activate(GtkApplication *app, gpointer user_data) {
    (void)user_data;

    static bool once = false;
    if (!once) {
        apply_demo_theme();
        once = true;
    }

    GtkWidget *window = create_window(app, &(window_config){
        .title = "Layout Stress API",
        .icon_name = "applications-development-symbolic",
        .default_width = 980,
        .default_height = 760,
        .resizable = true,
        .decorated = true,
    });

    container_add(window, build_layout_stress(), 0, 0, 0, 0);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("org.gtk.layoutstressapi", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
