
#include "io_utils.h"
#include "string_utils.h"

/*
typedef struct img3File {
    uint32_t magic;       // ASCII_LE("Img3")
    uint32_t fullSize;    // full size of fw image
    uint32_t sizeNoPack;  // size of fw image without header
    uint32_t sigCheckArea;// although that is just my name for it, this is the
                          // size of the start of the data section (the code) up to
                          // the start of the RSA signature (SHSH section)
    uint32_t ident;       // identifier of image, used when bootrom is parsing images
                          // list to find LLB (illb), LLB parsing it to find iBoot (ibot),
                          // etc.
    img3Tag  tags[];      // continues until end of file
};
typedef struct img3Tag {
    uint32_t magic;            // see below
    uint32_t totalLength;      // length of tag including "magic" and these two length values
    uint32_t dataLength;       // length of tag data
    uint8_t  data[dataLength];
    uint8_t  pad[totalLength - dataLength - 12]; // Typically padded to 4 byte multiple
};
*/

typedef struct
{
    uint32_t magic;
    uint32_t fullsize;
    uint32_t sizeNoPack;
    uint32_t sigCheckArea;
    uint32_t ident;
} img3;

typedef struct
{
    uint32_t magic;
    uint32_t totalLength;
    uint32_t dataLength;
    uint8_t *data;
    uint8_t *pad;
} img3tag;

void parseImg3(FILE *stream)
{
    img3 *img3file = (img3 *)malloc(sizeof(*img3file));
    char *data = readDataFromFileStream(stream);
    memcpy(img3file, data, sizeof(img3));
    const unsigned char *magic = convertUInt32ToASCII(img3file->magic);
    printf("Magic: %s\n", magic);
    printf("Packed size: %u\n", img3file->fullsize);
    printf("Unpacked size: %u\n", img3file->sizeNoPack);
    printf("sigCheckArea: %x\n", img3file->sigCheckArea);
    const unsigned char *ident = convertUInt32ToASCII(img3file->ident);
    printf("ident: %s\n", ident);
    // This code is horrible, but it "works" up until it seg faults! Lovely :P
    /*
    img3tag *tag = (img3tag *)malloc(sizeof(*tag));
    for (uint32_t i = sizeof(*img3file); i < img3file->sizeNoPack; i += sizeof(*tag))
    {
        memcpy(tag, data + i, sizeof(*tag));
        const unsigned char *tagMagic = convertUInt32ToASCII(tag->magic);
        printf("Tag Magic: %s\n", tagMagic);
        printf("Length: %u\n", tag->totalLength);
        printf("Data length: %u\n", tag->dataLength);
        tag->data = (uint8_t *)malloc(sizeof(*tag->data) * tag->dataLength);
        memcpy(tag->data, data + i + sizeof(uint32_t) * 3, sizeof(uint8_t) * tag->dataLength); // FIXME
        tag->pad = (uint8_t *)malloc(sizeof(*tag->pad) * tag->totalLength - tag->dataLength - 12);
        memcpy(tag->pad, data + i + sizeof(uint32_t) * 3 + sizeof(uint8_t) * tag->dataLength, sizeof(uint8_t) * tag->totalLength - tag->dataLength - 12);
    }
    free(tag);
    */
    free(data);
    free(img3file);
}