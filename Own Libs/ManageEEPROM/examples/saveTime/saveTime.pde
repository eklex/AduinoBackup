#include <ManageEEPROM.h>
#include <Time.h>

ManageEEPROM<time_t> mem(61);

void setup()
{
  Serial.begin(19200);
  setTime(20,24,00,12,10,2011);
  Serial.println(now());
}

void loop()
{
  unsigned int nb, i;
  String tmpString;
  
  if(Serial.available())
  {
    int val = Serial.read();
    if (val == 'a')
    {
      if(mem.saveData(now()))  Serial.println("done !");
      else Serial.println("add failed !");
    }
    else if (val == 'r')
    {
      Serial.print("Nombre d'effacement : ");
      Serial.println(mem.reset());
    }
    else if (val == 'n')
    {
      Serial.print(mem.number());
      Serial.println(" dates enregistrees");
    }
    else if (val == 'o')  Serial.print(mem.print());
    else if (val == 'p')
    {
      nb = mem.number();
      for(i=1;i<=nb;i++)  Serial.print(mem.printByNo(i));
    }
    else if (val == 'd')
    {
      i=0;
      tmpString = mem.printDebug(i);
      do
      {
        Serial.print(tmpString);
        i++;
        tmpString = mem.printDebug(i);
      }while(tmpString != "END");
    }
    else if (val == 'c')  Serial.println(mem.capacity(4));

  }
  delay(500);
}

