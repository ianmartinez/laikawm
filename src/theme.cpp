#include <png.h>
#include <iostream>
#include <memory>
#include <cstring>

using namespace std;

namespace LaikaWM {
	namespace Theming {
		enum class WidthMode {
			FullWidth = 0, // The titlebar is 100% the width of the window
			AutoWidth = 1 // The titlebar is only the size needed to display the title and titlebar buttons
		};
		
		enum class FillMode {
			Stretch = 0,
			Tile = 1
		};
		
		// Theme image
		class ThemeImage {
			public:
				string name;
				/* The path relative to the variant folder of the image's containing folder: */
				string folder;
				png_struct* raster;
				
				ThemeImage() {
					name = "";
					folder = "";
					raster = nullptr;
				}
				
				ThemeImage(string image_name, string image_folder) : 
					name(image_name), folder(image_folder) {
				}
				
				~ThemeImage() {
					//delete raster;
				}
				
				string getRasterFileName() {
					return "";
				}
				
				string getVectorFileName() {
					return "";
				}
				
				void renderRasterAtFactor(double factor) {
					
				}
		};

		/* A theme rect is a collection of theme resources that 
		   represents a part of the theme that 

		   Includes 4 corners, left, right, top, bottom, and interior
		 */
		struct Rect {
				/* A theme_rect will be stored inside a folder.

				A theme_rect with the name 'TitleBar' that has the 'Active' state
				and is part of section 'Window' in the default variant of a theme
				called 'SomeTheme' will be stored like this:
					SomeTheme/Default/Window/TitleBar/Active/
				And the individual files will be stored like this:
					SomeTheme/Default/Window/TitleBar/Active/TopLeft.svg
					SomeTheme/Default/Window/TitleBar/Active/TopRight.svg
					...
				*/
				string name;

				// Corners
				ThemeImage 
					top_left, top_right, bottom_left, bottom_right;

				// Sides
				ThemeImage
					top, bottom, left, right;
				
				ThemeImage interior;
				FillMode tile_interior;
		};

		struct Button {
			string name;
			ThemeImage
				normal, hover, active, clicked;
		};

		struct RectButton {
			string name;
			Rect
				normal, hover, active, clicked;
		};
	

		// Represents the 'taskbar' area
		struct Panel {
			Button main_button;
			RectButton secondary_button;
			Button window_button;
			ThemeImage splitter;
			Rect notification_area;
		};

		class Window {
			public:
				string name;
				WidthMode width;

				Rect
					border, title_bar, title_bar_text;
				
				Button 
					menu_button, shade_button, minimize_button, maximize_button, restore_button, close_button;
					
				Window(string window_name) {
					name = window_name;
					border.name = window_name + "Border";
					title_bar.name = window_name + "TitleBar";
					title_bar_text.name = window_name + "TitleBar";
					menu_button.name = window_name + "MenuButton";
					shade_button.name = window_name + "ShadeButton";
					minimize_button.name = window_name + "MinimizeButton";
					maximize_button.name = window_name + "MaximizeButton";
					restore_button.name = window_name + "RestoreButton";
					close_button.name = window_name + "CloseButton";
				}
		};
		
		void render(string vector_file, string raster_file, int width, int height) {
			string height_param = (height > 0) ? ("-h " + to_string(height)) : "";
			string width_param = (width > 0) ? ("-w " + to_string(width)) : "";
		
			const string command = "rsvg-convert " + width_param + " " + height_param + " " + vector_file + " -o " + raster_file;
			cout << command << endl;
			
			int status = system(command.c_str());
			
			if (status < 0)
				cout << "Render of " << vector_file << " failed: " << strerror(errno) << endl;
			else
			{
				if (WIFEXITED(status))
					cout << "Rendered " << vector_file << " to " << raster_file << endl;
				else
					cout << "Render of " << vector_file << " failed.";
			}
		}
		
		void renderAtFactor(ThemeImage* image, int factor) {
			
		}
		
		
		class ThemeVariant {
			public:
				string name;
				string folder;
				unique_ptr<Window> 
					active_wnd, inactive_wnd, maximized_wnd;
				
				ThemeVariant(string variant_name, string variant_folder) {
					name = variant_name;
					folder = variant_folder;
					
					active_wnd = make_unique<Window>("Active");
					inactive_wnd = make_unique<Window>("Inactive");
					maximized_wnd = make_unique<Window>("Maximized");
				}
				
				~ThemeVariant() {
					
				}
		};
	}
}

using namespace LaikaWM;

int main() {
	Theming::ThemeVariant* theme_var = new Theming::ThemeVariant("variant1", "themefolder");

	cout << "LaikaWM" << endl;
	cout <<  theme_var->name << endl;
	cout << theme_var->active_wnd->close_button.name << endl;
	cout << sizeof(*(theme_var->maximized_wnd)) << endl;
	
	system("cd ~/GitHub/laikawm/src");
	for(int i=100; i<=1000; i++) {
		Theming::render("test.svg", "testfolder/test" + to_string(i) +".png", i, 0);
	}
	
	
	return 0;
}
