
#include <io_utils.h>
#include <string_utils.h>

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
VERS: iBoot version of the image
SEPO: Security Epoch
SDOM: Security Domain
PROD: Production Mode
CHIP: Chip to be used with. example: 0x8900 for S5L8900.
BORD: Board to be used with
KBAG: Contains the IV and key required to decrypt; encrypted with the GID Key
SHSH: RSA encrypted SHA1 hash of the file
CERT: Certificate
ECID: Exclusive Chip ID unique to every device
TYPE: Type of image, should contain the same string as the header's ident
DATA: Real content of the file
NONC: Nonce used when file was signed.
CEPO: Chip epoch
OVRD:
RAND:
SALT:
*/

typedef struct
{
    uint32_t magic;
    uint32_t totalLength;
    uint32_t dataLength;
    uint8_t *data;
    uint8_t *pad;
} img3tag;

typedef struct
{
    uint32_t magic;
    uint32_t fullsize;
    uint32_t sizeNoPack;
    uint32_t sigCheckArea;
    uint32_t ident;
    img3tag **tags;
} img3;

img3tag *parseImg3Tag(uint8_t *data)
{
    img3tag *tag = (img3tag *)malloc(sizeof(*tag));
    uint32_t img3tagheadsize = sizeof(uint32_t) * 3;
    memcpy(tag, data, img3tagheadsize);
    tag->data = (uint8_t *)malloc(sizeof(uint8_t) * tag->dataLength);
    memcpy(tag->data, data + img3tagheadsize, sizeof(uint8_t) * tag->dataLength);
    uint32_t padding = sizeof(uint8_t) * tag->totalLength - tag->dataLength - 12;
    tag->pad = (uint8_t *)malloc(padding);
    memcpy(tag->pad, data + img3tagheadsize + tag->dataLength, padding);
    return tag;
}

img3 *parseImg3File(uint8_t *data)
{
    img3 *img3file = (img3 *)malloc(sizeof(*img3file));
    uint32_t img3headsize = sizeof(uint32_t) * 5;
    memcpy(img3file, data, img3headsize);
    img3file->tags = (img3tag **)malloc(sizeof(*img3file->tags));
    return img3file;
}

void parseImg3(FILE *stream)
{
    int8_t *data = readDataFromFileStream(stream);
    img3 *img3file = parseImg3File((uint8_t *)data);
    printf("Img3 magic: %s\n", convertUInt32ToASCII(img3file->magic));
    printf("Packed size: %u\n", img3file->fullsize);
    printf("Unpacked size: %u\n", img3file->sizeNoPack);
    printf("sigCheckArea: %u\n", img3file->sigCheckArea);
    printf("Ident: %s\n", convertUInt32ToASCII(img3file->ident));
    /*
    printf("Tag: %s", convertUInt32ToASCII(tag->magic));
    printf("Magic: %s\n", convertUInt32ToASCII(tag->magic));
    printf("Total length: %u\n", tag->totalLength);
    printf("Data length: %u\n", tag->dataLength);
    */
    free(img3file->tags);
    free(img3file);
    free(data);
}