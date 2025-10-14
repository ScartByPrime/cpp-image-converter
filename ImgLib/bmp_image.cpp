#include "bmp_image.h"
extern "C" {
#include "pack_defines.h"
}

#include <array>
#include <fstream>
#include <string_view>

using namespace std;

namespace img_lib {

    PACKED_STRUCT_BEGIN BitmapFileHeader{
        uint16_t signature;
        uint32_t file_size;
        uint32_t reserved;
        uint32_t data_offset;
    }
    PACKED_STRUCT_END

    PACKED_STRUCT_BEGIN BitmapInfoHeader{
        uint32_t header_size;        // Размер заголовка
        int32_t  width;              // Ширина в пикселях
        int32_t  height;             // Высота в пикселях
        uint16_t planes;             // Количество плоскостей (всегда 1)
        uint16_t bit_count;          // Бит на пиксель (24)
        uint32_t compression;        // Тип сжатия (0 = BI_RGB)
        uint32_t image_size;         // Размер данных (байт)
        int32_t  x_pixels_per_m;     // Горизонтальное разрешение (11811)
        int32_t  y_pixels_per_m;     // Вертикальное разрешение (11811)
        uint32_t colors_used;        // Использованные цвета (0)
        uint32_t colors_important;   // Важные цвета (0x1000000)
    }
    PACKED_STRUCT_END

        // функция вычисления отступа по ширине
    static int GetBMPStride(int w) {
        return 4 * ((w * 3 + 3) / 4);
    }

    // напишите эту функцию
    bool SaveBMP(const Path& file, const Image& image) {
        if (!image) {
            return false;
        }

        int width = image.GetWidth();
        int height = image.GetHeight();
        int stride = GetBMPStride(width);
        int image_size = stride * height;

        ofstream out(file, ios::binary);
        if (!out) {
            return false;
        }

        // File Header
        BitmapFileHeader file_header;
        file_header.signature = 0x4D42;
        file_header.file_size = sizeof(BitmapFileHeader) +
            sizeof(BitmapInfoHeader) +
            image_size;
        file_header.reserved = 0;
        file_header.data_offset = sizeof(BitmapFileHeader) +
            sizeof(BitmapInfoHeader);

        // Info Header
        BitmapInfoHeader info_header;
        info_header.header_size = sizeof(BitmapInfoHeader);
        info_header.width = width;
        info_header.height = height;
        info_header.planes = 1;
        info_header.bit_count = 24;
        info_header.compression = 0;
        info_header.image_size = image_size;
        info_header.x_pixels_per_m = 11811;
        info_header.y_pixels_per_m = 11811;
        info_header.colors_used = 0;
        info_header.colors_important = 0x1000000;

        // Пишем заголовки
        out.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
        out.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));

        std::vector<char> buff(stride);

        for (int y = 0; y < height; ++y) {
            const Color* line = image.GetLine((height - 1) - y);

            for (int x = 0; x < width; ++x) {
                buff[x * 3 + 0] = static_cast<char>(line[x].b);
                buff[x * 3 + 1] = static_cast<char>(line[x].g);
                buff[x * 3 + 2] = static_cast<char>(line[x].r);
            }

            // padding
            for (int p = width * 3; p < stride; ++p) {
                buff[p] = 0;
            }

            out.write(buff.data(), stride);
        }

        return true;
    }


    // напишите эту функцию
    Image LoadBMP(const Path& file) {
        ifstream ifs(file, ios::binary);
        if (!ifs) {
            return Image{};
        }

        BitmapFileHeader file_header;
        BitmapInfoHeader info_header;

        // Читаем заголовки
        ifs.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
        ifs.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

        // Проверка формата
        if (file_header.signature != 0x4D42) { // 'BM'
            return Image{};
        }
        if (info_header.bit_count != 24 || info_header.compression != 0) {
            return Image{};
        }

        int width = info_header.width;
        int height = info_header.height;
        if (width < 0 || height < 0) {
            return Image{};
        }
        int stride = GetBMPStride(width);

        Image result(width, height, Color::Black());

        ifs.seekg(file_header.data_offset, ios::beg);

        std::vector<char> buff(stride);

        for (int y = 0; y < height; ++y) {
            Color* line = result.GetLine((height - 1) - y);
            ifs.read(buff.data(), stride);

            for (int x = 0; x < width; ++x) {
                line[x].b = static_cast<byte>(buff[x * 3 + 0]);
                line[x].g = static_cast<byte>(buff[x * 3 + 1]);
                line[x].r = static_cast<byte>(buff[x * 3 + 2]);
            }
        }

        return result;

    }

}  // namespace img_lib