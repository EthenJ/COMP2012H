#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

enum display_type {
	EMPTY, FILLED, STAR, CROSS
};

class Display {
public:
    Display(const int& size, const int& scale) : SIZE(size), CENTER((size + 1) / 2), SCALE(scale) {
        frame_buffer = new display_type * [size * 2];
        for (int i = 0; i < size * 2; ++i) {
            frame_buffer[i] = new display_type[size];
        }

        ostringstream strout;
        for (int i = 0; i < size * 2; ++i) {
            strout << endl;
        }
        clear_screen = strout.str();
    }

    ~Display() {
        for (int i = 0; i < SIZE * 2; ++i) {
            delete[] frame_buffer[i];
        }
        delete[] frame_buffer;
    }

    Display(const Display&) = delete;
    void operator=(const Display&) = delete;

	// Allow for a center coordinate (0,0), hence odd size
	const int SIZE;
	const int CENTER;

	// How large a unit (in the Cartesian coordinate system of physics simulation) is displayed on the screen
	const int SCALE;

    // By default, console display has height equal to double that of width (in screen pixels)
    // Each 'console pixel' thus has two character width and one character high
    // The (0,0) coordinate corresponds to the center 'console pixel' in the SIZE x SIZE 'console pixel grid'
    display_type** frame_buffer;

    // A string to clear the whole screen (using endl's)
    string clear_screen;

    void clear_entire_display() {
        cout << clear_screen;
    }

    /**
    * Clears the frame buffer (setting all to empty)
    */
    void clear_frame_buffer() {
        for (int y = 0; y < SIZE; ++y) {
            for (int x = 0; x < SIZE * 2; ++x) {
                frame_buffer[x][y] = EMPTY;
            }
        }
    }

    /**
    * Inputs a bounds of a rectangle (ax,ay,bx,by) in the Cartesian coordinate system
    * and outputs a bounds of a rectangle in the 'console display' coordinate system.
    *
    * Note that ax<bx, ay<by, cx<dx, cy<dy
    */
    void get_frame_bounding_rect(const double& ax, const double& ay, const double& bx, const double& by, int& cx, int& cy, int& dx, int& dy) {
        cx = (int)floor(ax * SCALE + CENTER);
        dx = (int)ceil(bx * SCALE + CENTER);

        dy = (int)ceil(CENTER - ay * SCALE);
        cy = (int)floor(CENTER - by * SCALE);
    }

    /**
    * Translates (x,y), the coordinates (of the frame buffer) into
    * (cx,cy), the coordinates of the physics simulation
    */
    void to_coordinates(const int& x, const int& y, double& cx, double& cy) {
        cx = (double)x - CENTER;
        cy = CENTER - (double)y; // Inverted, for Cartesian coordinates (positive points upwards)

        cx /= SCALE;
        cy /= SCALE;
    }

    /**
    * Inputs are in Cartesian coordinates (of physics simulation). Sets the frame buffer to the corresponding type.
    */
    void draw_circle(double circle_x, double circle_y, double radius, display_type type) {
        int cx, cy, dx, dy;
        get_frame_bounding_rect(circle_x - radius, circle_y - radius, circle_x + radius, circle_y + radius, cx, cy, dx, dy);
        for (int x = max(cx, 0); x <= min(dx, SIZE - 1); ++x) {
            for (int y = max(cy, 0); y <= min(dy, SIZE - 1); ++y) {
                double fx, fy;
                to_coordinates(x, y, fx, fy); // Convert back to Cartesian
                if (hypot(fx - circle_x, fy - circle_y) < radius) {
                    frame_buffer[2 * x][y] = type;
                    frame_buffer[2 * x + 1][y] = type;
                }
            }
        }
    }

    /**
    * Renders the frame buffer onto the console
    */
    void draw_frame() {
        ostringstream strout;
        for (int y = 0; y < SIZE; ++y) {
            for (int x = 0; x < SIZE * 2; ++x) {
                switch (frame_buffer[x][y]) {
                case EMPTY:
                    strout << ".";
                    break;
                case FILLED:
                    strout << "O";
                    break;
                case STAR:
                    strout << "*";
                    break;
                case CROSS:
                    strout << "+";
                    break;
                }
            }
            strout << endl;
        }
        cout << strout.str();
    }

    /**
    * Clears the console and renders the frame buffer onto the console
    */
    void clear_and_draw_frame() {
        ostringstream strout;
        strout << "_______________________________________________________________________________________________________________________" << endl;
        for (int y = 0; y < SIZE; ++y) {
            for (int x = 0; x < SIZE * 2; ++x) {
                switch (frame_buffer[x][y]) {
                case EMPTY:
                    strout << ".";
                    break;
                case FILLED:
                    strout << "O";
                    break;
                case STAR:
                    strout << "*";
                    break;
                case CROSS:
                    strout << "+";
                    break;
                }
            }
            strout << endl;
        }
        cout << strout.str();
    }
}editing_display(51,1), animation_display(151,3);