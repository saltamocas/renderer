#include <mapnik/map.hpp>
#include <mapnik/box2d.hpp>
#include <mapnik/load_map.hpp>
#include <mapnik/projection.hpp>
#include <mapnik/agg_renderer.hpp>
#include <mapnik/image.hpp>
#include <mapnik/image_util.hpp>
#include <mapnik/datasource_cache.hpp>
#include <mapnik/font_engine_freetype.hpp>
#include <mapnik/version.hpp>
#include <sys/stat.h>
#include <time.h>

void help(const std::string& srs);
bool exist(const std::string& name);

int main(int argc, char **argv)
{
    mapnik::datasource_cache::instance().register_datasources("/usr/local/lib/mapnik/input");
    //mapnik::freetype_engine::register_fonts("/home/alf/MEOCloud/fonts");
    mapnik::Map *map;
    mapnik::projection *proj;
    mapnik::box2d<double> *box;
    const char *stylesheet = "";
    const char *png_filename = "out.png";
    const char *srs = "+init=epsg:3763";
    unsigned png_width = 400, png_height = 400;
    double x0 = -40, y0 = -40, x1 = 10, y1 = 10;
    int i;
    std::cout << "Mapnik " << MAPNIK_VERSION_STRING << "\n";
    if( argc == 1 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help") )
        help(srs);
    for( i = 1; i < argc && argv[i][0] == '-' && strlen(argv[i]) == 2; i += 2 ) {
        if( i > argc - 2 ) {
            std::cout << "Missing argument to option " << argv[i] << ".\n";
            help(srs);
        }
        if( argv[i][1] == 'o' )
            png_filename= argv[i+1];
        else if( argv[i][1] == 'r' )
        	srs = argv[i+1];
        else if( argv[i][1] == 'w' )
            png_width= strtoul(argv[i+1], NULL, 10);
        else if( argv[i][1] == 'x')
        	std::stringstream(argv[i+1]) >> x0;
        else if( argv[i][1] == 'X')
        	std::stringstream(argv[i+1]) >> x1;
        else if( argv[i][1] == 'y')
        	std::stringstream(argv[i+1]) >> y0;
        else if( argv[i][1] == 'Y')
        	std::stringstream(argv[i+1]) >> y1;
        else if( argv[i][1] == 'h' )
            png_height= strtoul(argv[i+1], NULL, 10);
        else if( argv[i][1] == 's' )
            stylesheet= argv[i+1];
        else {
            std::cout <<"Unknown option " << argv[i] << ".\n";
            help(srs);
        }
    }
    if (stylesheet == "") {
    	std::cout << "Missing stylesheet.\n";
    	std::cout << "render --help for more info.\n";
    	exit(2);
    	}
    if (!exist(stylesheet)) {
    	std::cout << "Style sheet " << stylesheet << " not found.\n";
    	exit(1);
    	}
    std::cout << "\nbbox: " << x0 <<", " << y0 <<", " << x1 <<", " << y1 << "\n";
    std::cout << "image size: " << png_width << "x" << png_height << "\n";
    std::cout << "srs: " << srs << "\n";
    std::cout << "Rendering " << stylesheet << " to " << png_filename << "." <<std::endl;
    box = new mapnik::box2d<double>(x0, y0, x1, y1);
    map = new mapnik::Map(png_width, png_height, srs);
    mapnik::load_map(*map, stylesheet);
    map->zoom_to_box(*box);
    mapnik::image_rgba8 im(png_width ,png_height, srs);
    mapnik::agg_renderer<mapnik::image_rgba8> ren(*map, im);
    ren.apply();
    mapnik::save_to_file(im, png_filename);
    std::cout << "Done." << std::endl;
	}
bool exist(const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}
void help(const std::string& srs ) {
    std::cout <<
    "XML mapnik renderer\n\n"
	"render <options>\n\nOptions:\n"
	"-s <style.xml>      XML style file\n"
    "-r srs              proj4 projection, defaults to '" << srs << "'\n"
	"-o <output.png>     Output file. Must include extension png, jpg or tif. Defaults to out.png\n"
	"-w <width>          Width of output image in pixels (defaults to 400)\n"
	"-h <height>         Height of output image in pixels (defaults to 400)\n"
	"-x <coordinate>     top x coordinate of area\n"
	"-y <coordinate>     top y coordinate of area\n"
	"-X <coordinate>     bottom x coordinate of area\n"
	"-Y <coordinate>     bottom y coordinate of area\n" << std::endl;
    exit(1);
}
