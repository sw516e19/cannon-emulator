#include "stdio.h"

#ifdef _WIN32
#include "windows.h"
#else
#include <unistd.h>
#endif

#include "stdint.h"

typedef struct {
    uint16_t sync; //!< \~English Sync bytes
    uint8_t packet_type; //!< \~English Packet type
    uint8_t payload_length; //!< \~English Payload length
    uint16_t checksum; //!< \~English Checksum (Sum of all bytes in payload)

} pixycam2_response_header_t;

/**
 * \~English
 * \brief Structure for the blocks from Pixy2 camera
 */
typedef struct {
    uint16_t signature; //!< \~English Signature number / Color code number (0-255)
    uint16_t x_center; //!< \~English X (center) of block in pixel (0-315)
    uint16_t y_center; //!< \~English Y (center) of block in pixel (0-207)
    uint16_t width; //!< \~English Width of block in pixel (0-316)
    uint16_t height; //!< \~English Height of block in pixel (0-208)
    int16_t color_angle; //!< \~English Angle of color-code in degrees (-180-180, 0 if not a color code)
    uint8_t tracking_index; //!< \~English Tracking index of block (0-255)
    uint8_t age; //!< \~English Number of frames this block has been tracked (0-255, stops incrementing at 255)

} pixycam2_block_t;

/**
 * \~English
 * \brief Structure for containing header and blocks from Pixy2 camera
 */
typedef struct {
    pixycam2_response_header_t header; //!< \~English headerpackage
    pixycam2_block_t* blocks; //!< \~English block-pointer

} pixycam2_block_response_t;

int should_shoot = 0;
int new_data = 0;

// The task responsible for detecting the falling object using the pixycam
int detect_task()
{
    // Fake sleep simulating grabbing pixycam data. Worst case is 17 miliseconds
    Sleep(17);

    // TODO: ADD SAMPLE PIXYCAM BLOCK DATA
}

// The task for calculating distances using the retrieved pixycam data
int calculate_task()
{
    // If no new pixycam data, just skip
    if (new_data == 0)
        return 0;

    return 0;
}

// The task that has the responsibility for shooting the falling object
int shoot_task()
{
    // Check if we should shoot
    if (should_shoot == 0)
        return 0;

    // SHOOT!
}


 
int main(int argc, char *argv[])
{
    int tick_count = 0;
    while (1)
    {
        detect_task();
        calculate_task();
        shoot_task();
        Sleep(10);

        tick_count++;
        printf("Tick %d\n", tick_count);
    }
    return 0;
}