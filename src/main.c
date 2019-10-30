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
    pixycam2_block_t blocks[5]; //!< \~English block-pointer. 5 objects can be tracked at a time.

} pixycam2_block_response_t;

int should_shoot = 0;
int new_data = 0;
pixycam2_block_response_t sample_block_response;
int tick_count = 0;

unsigned long long first_block_time;
unsigned long long current_block_time;


// The task responsible for detecting the falling object using the pixycam
int detect_task()
{
    // Fake sleep simulating grabbing pixycam data. Worst case is 17 miliseconds
    Sleep(17);

    // Simulate blocks of the falling object
    if (tick_count == 3)
    {
        first_block_time = GetTickCount64();


        found_block(100, 207);
    }


    if (tick_count == 4)
    {
        found_block(100, 165);
    }


    if (tick_count == 5)
    {
        found_block(100, 132);
    }


    return 0;
}

// The task for calculating distances using the retrieved pixycam data
int calculate_task()
{
    // If no new pixycam data, just skip
    if (new_data == 0)
        return 0;

    new_data = 0;

    return 0;
}

// The task that has the responsibility for shooting the falling object
int shoot_task()
{
    // Check if we should shoot
    if (should_shoot == 0)
        return 0;

    // SHOOT!
    Sleep(50);

    return 0;
}

// Helper method for signifying a block was found
int found_block(uint16_t x_center, uint16_t y_center)
{
    // Set that there has been found new data
    new_data = 1;

    // Set the block header
    sample_block_response.header.checksum = 0;
    sample_block_response.header.packet_type = 0;
    sample_block_response.header.payload_length = 0;
    sample_block_response.header.sync = 0;

    // Set the block data
    sample_block_response.blocks[0].age = 0;
    sample_block_response.blocks[0].color_angle = 0;
    sample_block_response.blocks[0].height = 0;
    sample_block_response.blocks[0].signature = 0;
    sample_block_response.blocks[0].tracking_index = 0;
    sample_block_response.blocks[0].width = 0;
    sample_block_response.blocks[0].x_center = x_center;
    sample_block_response.blocks[0].y_center = y_center;

    printf("%d\n", sample_block_response.blocks[0].y_center);

    return 0;
}


 
int main(int argc, char *argv[])
{
    while (1)
    {
        detect_task();
        calculate_task();
        shoot_task();
        Sleep(10);

        tick_count++;
        //printf("Tick %d\n", tick_count);
    }
    return 0;
}