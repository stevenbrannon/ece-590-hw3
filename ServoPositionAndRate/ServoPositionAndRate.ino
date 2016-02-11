/* Source for HW3.
 * Goal: "make one xl-320 servo move from 45 deg to 90 deg with a period of 
 * 2 seconds and a second move from 0 to 180 with a period of 1 second."
 *
 * This assumes that 2 servos have been previously configured with IDs 1 and 2.
 *
 * Steven Brannon 2.10.26
 * With code generously borrowed from http://wiki.lofarolabs.com/index.php/OpenCM_9.04
 */


/* Serial device defines for dxl bus */
#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04

#define J_ID_45_90 1
#define J_ID_0_180 2

/* Using the values from http://support.robotis.com/en/product/dynamixel/xl-320/xl-320.htm
 * we'll define the constants needed to set the various parameters
 * Goal Position is set from 0-1023 in units of 0.29 degrees
 */
#define DEG_0       0
#define DEG_45      155
#define DEG_90      310
#define DEG_180     621

Dynamixel Dxl(DXL_BUS_SERIAL1);

void setup()
{
  // Initialize the dynamixel bus:
  // Dynamixel 2.0 Baudrate -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps  
  Dxl.begin(3);  
  Dxl.jointMode(BROADCAST_ID);
  
  /* initialize to the initial positions */
  Dxl.goalPosition(J_ID_0_180, DEG_0);
  Dxl.goalPosition(J_ID_45_90, DEG_45);

}

void loop() {
  /* To setup the desired rate an action needs to occur every 500ms.
   * Since we don't need to do anything else complex we'll just use a 
   * series of delays.
   */
   
   /* At t = 0 set both servos to their 'high' positions */
   Dxl.goalPosition(J_ID_0_180, DEG_180);
   Dxl.goalPosition(J_ID_45_90, DEG_90);
   
   delay(500);
   
   /* At t = 0.5 set the servo with the 1s period back to its original position */
   Dxl.goalPosition(J_ID_0_180, DEG_0);
   
   delay(500);
   
   /* At t= 1 set the servo with a period of 2s back to its origonal position 
    * and restart the sequence for the other servo 
    */
   Dxl.goalPosition(J_ID_45_90, DEG_45);
   Dxl.goalPosition(J_ID_0_180, DEG_180);
   
   delay(500);
   
   /* At t = 1.5 set the servo with a period of 1s back to its original position */
   Dxl.goalPosition(J_ID_0_180, DEG_0);
   
   delay(500);
}

