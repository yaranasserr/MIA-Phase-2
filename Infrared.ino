#include <SparkFun_APDS9960.h>
#include <Wire.h>
void read_color(){
  // Read the light levels (ambient, red, green, blue)
  apds.readAmbientLight(ambient_light);
  apds.readRedLight(red_light);
  apds.readGreenLight(green_light);
  apds.readBlueLight(blue_light);

  detect_color(ambient_light,red_light,green_light,blue_light);

}

void detect_color(uint16_t ambient_light,uint16_t red_light,uint16_t green_light,uint16_t blue_light){
  //warning!
  //light values should be changed after detecting each color
  if(ambient_light > 0 && ambient_light < 0 && red_light > 0 && red_light < 0 && green_light > 0 && green_light < 0 && blue_light > 0 && blue_light < 0)
    {
      green_cntr++;
    }
  else if(ambient_light > 0 && ambient_light < 0 && red_light > 0 && red_light < 0 && green_light > 0 && green_light < 0 && blue_light > 0 && blue_light < 0)
    {
      red_cntr++;
    }
  else if(ambient_light > 0 && ambient_light < 0 && red_light > 0 && red_light < 0 && green_light > 0 && green_light < 0 && blue_light > 0 && blue_light < 0)
    {
      yellow_cntr++;
    }
  else if(ambient_light > 0 && ambient_light < 0 && red_light > 0 && red_light < 0 && green_light > 0 && green_light < 0 && blue_light > 0 && blue_light < 0)
    {
      gray_cntr++;
    }
  else{
    return;
  }
}