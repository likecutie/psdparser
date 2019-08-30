#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
#include <fstream>

/*part 1*/
typedef struct FileHeader_t {
	uchar signature[4] = { '8','B','P','S' };;
	uint16_t version = 1;
	uchar reserved[6];
	uint16_t channels;
	uint32_t height;
	uint32_t width;
	uint16_t depth;
	uint16_t colorMode;
}FileHeader;

void writeFileHeader(FILE* file, FileHeader* fileHeader) {
	fwrite(fileHeader->signature, 1, 4, file);
	fwrite(&fileHeader->version, 2, 1, file);
	fwrite(fileHeader->reserved, 1, 6, file);
	fwrite(&fileHeader->channels, 2, 1, file);
	fwrite(&fileHeader->height, 4, 1, file);
	fwrite(&fileHeader->width, 4, 1, file);
	fwrite(&fileHeader->depth, 2, 1, file);
	fwrite(&fileHeader->colorMode, 2, 1, file);
}

void createFileHeader(FileHeader* fileHeader, uint16_t channels, uint32_t height, uint32_t width, uint16_t depth, uint16_t colorMode) {
	fileHeader->reserved[6] = { 0 };
	fileHeader->channels = channels;
	fileHeader->height = height;
	fileHeader->width = width;
	fileHeader->depth = depth;
	fileHeader->colorMode = colorMode;
}

/*part 2*/
typedef struct ColorModeData_t {
	uint32_t dataLength = 0;
}ColorModeData;

void writeColorModeData(FILE* file, ColorModeData* colorModeData) {
	fwrite(&colorModeData->dataLength, 4, 1, file);
}

void createColorModeData() {
	//do nothing
}

/*part 3*/
typedef struct ImageResources_t{
	uint32_t resourceLength = 0;
}ImageResources;

void writeImageResources(FILE* file,ImageResources* resouces){
	fwrite(&resouces->resourceLength, 4, 1, file);
}

void createImageResources() {
	//do nothing
}

/*part 4*/
typedef struct LayerBlendingRanges_t{
	unsigned int length;
	uchar compositeGrayBlendSource[4];
	uchar compositeGrayBlend[4];
	unsigned int *ranges;
}LayerBlendingRanges;

typedef struct LayerRecords_t {
	unsigned int corner[4];
	unsigned short channelNum;
	char* channelInformation;
	char bim[4] = { '8','B','I', 'M' };
	char blendModeKey[4] = { 'n','o','r', 'm' };
	uchar opacity;
	uchar clipping;
	uchar flags;
	uchar filter;
	unsigned int extraDataField;
	uchar noneMask[4];
	LayerBlendingRanges* lbr;
	uchar layerName[4] = { 'n', 'o', 'n', 'e' };
}LayerRecords;

void writeLayerBlendingRanges(FILE* file, LayerBlendingRanges* layerBlendingRanges) {
	fwrite(&layerBlendingRanges->length, 4, 1, file);
	fwrite(layerBlendingRanges->compositeGrayBlendSource, 1, 4, file);
	fwrite(layerBlendingRanges->compositeGrayBlend, 1, 4, file);
	int rangeslen = layerBlendingRanges->length - 12;
	fwrite(layerBlendingRanges->ranges, 1, rangeslen, file);
}

void createLayerBlendingRanges(LayerRecords* layerRecords,LayerBlendingRanges* layerBlendingRanges) {
	int nth = layerRecords->channelNum;
	layerBlendingRanges->length = 12 + 8 * nth;
	layerBlendingRanges->compositeGrayBlendSource[4] = { 0 };/////没看懂
	layerBlendingRanges->compositeGrayBlend[4] = { 0 };////////没看懂
	layerBlendingRanges->ranges = new uint32_t[nth * 8];/////暂不知填什么
}

void writeLayerRecords(FILE* file, LayerRecords* layerRecords) {
	fwrite(layerRecords->corner, 4, 4, file);
	fwrite(&layerRecords->channelNum, 2, 1, file);
	fwrite(layerRecords->channelInformation, 1, 6 * layerRecords->channelNum, file);
	fwrite(layerRecords->bim, 1, 4, file);
	fwrite(layerRecords->blendModeKey, 1, 4, file);
	fwrite(&layerRecords->opacity, 1, 1, file);
	fwrite(&layerRecords->clipping, 1, 1, file);
	fwrite(&layerRecords->flags, 1, 1, file);
	fwrite(&layerRecords->filter, 1, 1, file);
	//...
	writeLayerBlendingRanges(file, layerRecords->lbr);
	//...
}

void createLayerRecords() {
	//...
}

typedef struct ChannelImageData_t {
	unsigned short compression;
	uchar* imageData;
}ChannelImageData;

void writeChannelImageData(FILE* file, ChannelImageData* channelImageData) {
	//...
}

void createChannelImageData(ChannelImageData* channelImageData) {
	//...
}

typedef struct LayerInfo_t {
	unsigned int length;
	unsigned short layerCount;
	LayerRecords* layerRecords;
	ChannelImageData* channelImageData;
}LayerInfo;

void writeLayerInfo(FILE* file, LayerInfo* layerInfo) {
	//...
}

void createLayerInfo(LayerInfo* layerinfo) {
	//...
}

typedef struct GlobalLayerMaskInfo_t {
	unsigned int length;
}GlobalLayerMaskInfo;

void writeGlobalLayerMaskInfo(FILE* file, GlobalLayerMaskInfo* globalLayerMaskInfo) {
	//...
}

void createGlobalLayerMaskInfo(GlobalLayerMaskInfo* globalLayerMaskInfo) {
	//...
}

typedef struct LayerAndMaskInformation_t {
	uint32_t informationLength = 0;
	LayerInfo* layerInfo;
	GlobalLayerMaskInfo* globalLayerMaskInfo;
}LayerAndMaskInformation;

void writeLayerAndMaskInformation(FILE* file, LayerAndMaskInformation information) {
	//...
}

void createLayerAndMaskInfomation(LayerAndMaskInformation* information) {
	//...
}

typedef struct ImageData_t {
	ImageData_t(int len) {
		data = new uchar[len];
	};
	~ImageData_t() {
		delete[] data;
	};
	uint16_t compressionMethod = 0;
	uchar* data;
}ImageData;

void writeImageData(FILE* file, ImageData imageData) {
	//...
}

void createImageData(ImageData* imageData) {
	//...
}

int main(void) {
	FileHeader* fileHeader;
	ColorModeData* colorModeData;
	ImageResources* imageResources;
	LayerAndMaskInformation* information;
	//...

	return 0;
}
