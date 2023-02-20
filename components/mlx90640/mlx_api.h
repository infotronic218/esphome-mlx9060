#ifndef __MLX_API__
#define __MLX_API__
#include <stdint.h>
#include "mlx_driver.h"
#define SCALEALPHA 0.000001

typedef struct {
    int16_t kVdd;
    int16_t vdd25;
    float KvPTAT;
    float KtPTAT;
    uint16_t vPTAT25;
    float alphaPTAT;
    int16_t gainEE;
    float tgc;
    float cpKv;
    float cpKta;
    uint8_t resolutionEE;
    uint8_t calibrationModeEE;
    float KsTa;
    float ksTo[5];
    int16_t ct[5];
    uint16_t alpha[768];
    uint8_t alphaScale;
    int16_t offset[768];
    int8_t kta[768];
    uint8_t ktaScale;
    int8_t kv[768];
    uint8_t kvScale;
    float cpAlpha[2];
    int16_t cpOffset[2];
    float ilChessC[3];
    uint16_t brokenPixels[5];
    uint16_t outlierPixels[5];
} paramsMLX90640;
namespace esphome
{
    namespace mlx90640_app
    {
        class MLXApi{
            private:
            MLXDriver *driver ;
            public:
                MLXApi(MLXDriver *driver);
                int MLX90640_DumpEE(uint8_t slaveAddr, uint16_t *eeData);
                int MLX90640_GetFrameData(uint8_t slaveAddr, uint16_t *frameData);
                int MLX90640_ExtractParameters(uint16_t *eeData, paramsMLX90640 *mlx90640);
                float MLX90640_GetVdd(uint16_t *frameData, const paramsMLX90640 *params);
                float MLX90640_GetTa(uint16_t *frameData, const paramsMLX90640 *params);
                void MLX90640_GetImage(uint16_t *frameData, const paramsMLX90640 *params, float *result);
                void MLX90640_CalculateTo(uint16_t *frameData, const paramsMLX90640 *params,  float emissivity, float tr, float *result);
                int MLX90640_SetResolution(uint8_t slaveAddr, uint8_t resolution);
                int MLX90640_GetCurResolution(uint8_t slaveAddr);
                int MLX90640_SetRefreshRate(uint8_t slaveAddr, uint8_t refreshRate);
                int MLX90640_GetRefreshRate(uint8_t slaveAddr);
                int MLX90640_GetSubPageNumber(uint16_t *frameData);
                int MLX90640_GetCurMode(uint8_t slaveAddr);
                int MLX90640_SetInterleavedMode(uint8_t slaveAddr);
                int MLX90640_SetChessMode(uint8_t slaveAddr);
                void MLX90640_BadPixelsCorrection(uint16_t *pixels, float *to, int mode, paramsMLX90640 *params);

                void ExtractVDDParameters(uint16_t *eeData, paramsMLX90640 *mlx90640);
                void ExtractPTATParameters(uint16_t *eeData, paramsMLX90640 *mlx90640);
                void ExtractGainParameters(uint16_t *eeData, paramsMLX90640 *mlx90640);
                void ExtractTgcParameters(uint16_t *eeData, paramsMLX90640 *mlx90640);
                void ExtractResolutionParameters(uint16_t *eeData, paramsMLX90640 *mlx90640);
                void ExtractKsTaParameters(uint16_t *eeData, paramsMLX90640 *mlx90640);
                void ExtractKsToParameters(uint16_t *eeData, paramsMLX90640 *mlx90640);
                void ExtractAlphaParameters(uint16_t *eeData, paramsMLX90640 *mlx90640);
                void ExtractOffsetParameters(uint16_t *eeData, paramsMLX90640 *mlx90640);
                void ExtractKtaPixelParameters(uint16_t *eeData, paramsMLX90640 *mlx90640);
                void ExtractKvPixelParameters(uint16_t *eeData, paramsMLX90640 *mlx90640);
                void ExtractCPParameters(uint16_t *eeData, paramsMLX90640 *mlx90640);
                void ExtractCILCParameters(uint16_t *eeData, paramsMLX90640 *mlx90640);
                int ExtractDeviatingPixels(uint16_t *eeData, paramsMLX90640 *mlx90640);
                int CheckAdjacentPixels(uint16_t pix1, uint16_t pix2);
                float GetMedian(float *values, int n);
                int IsPixelBad(uint16_t pixel, paramsMLX90640 *params);

        };
    }

}

#endif