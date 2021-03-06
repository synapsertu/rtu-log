/*
        The MIT License (MIT)

        Copyright (c) 2021 Andrew O'Connell

        Permission is hereby granted, free of charge, to any person obtaining a copy
        of this software and associated documentation files (the "Software"), to deal
        in the Software without restriction, including without limitation the rights
        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
        copies of the Software, and to permit persons to whom the Software is
        furnished to do so, subject to the following conditions:

        The above copyright notice and this permission notice shall be included in all
        copies or substantial portions of the Software.

        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
        SOFTWARE.
				
*/	


void displayDigOutValues(int deviceId, int displayType)
{
	int regId;
	const char *chMode[4];
				chMode[0] = "Level";
				chMode[1] = "Level";
				chMode[2] = "Pulse Freq";
				chMode[3] = "Pulse Count";


	// initialise these to zero or else we'll get nonsense readings shown if the chan/register 
	// is not enabled in the config.
	// You could initialise this to NaN or some other recognisable value to indicate "No reading available" 
	int chanLvl[9]={0};      // Values from index position 1 onwards
    int chanFreq[9]={0};
    int chanPulseCnt[9]={0};
    float pulseFreqTemp=0;

	for(regId=1 ; regId<(dataSource[deviceId].numRegisters+1) ; regId++)
	{	
		// Deals with chan 1 value registers
		if ( dataSource[deviceId].regAddress[regId] == 1  ) { chanLvl[1]      =dataSource[deviceId].value[regId]; }    // Level
		if ( dataSource[deviceId].regAddress[regId] == 10 ) { chanFreq[1]     =dataSource[deviceId].value[regId]; }    // Pulse Frequency 
		if ( dataSource[deviceId].regAddress[regId] == 11 ) { chanPulseCnt[1] =dataSource[deviceId].value[regId]; }    // Pulse Counter 
		
		// Deals with chan 2 value registers
		if ( dataSource[deviceId].regAddress[regId] == 2  ) { chanLvl[2]       =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 12 ) { chanFreq[2]      =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 13 ) { chanPulseCnt[2]  =dataSource[deviceId].value[regId]; }    
		
		// Deals with chan 3 value registers
		if ( dataSource[deviceId].regAddress[regId] == 3  ) { chanLvl[3]      =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 14 ) { chanFreq[3]     =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 15 ) { chanPulseCnt[3] =dataSource[deviceId].value[regId]; }    

		// Deals with chan 4 value registers
		if ( dataSource[deviceId].regAddress[regId] == 4  ) { chanLvl[4]       =dataSource[deviceId].value[regId]; }   
		if ( dataSource[deviceId].regAddress[regId] == 16 ) { chanFreq[4]      =dataSource[deviceId].value[regId]; }   
		if ( dataSource[deviceId].regAddress[regId] == 17 ) { chanPulseCnt[4]  =dataSource[deviceId].value[regId]; }   
		
		// Deals with chan 5 value registers
		if ( dataSource[deviceId].regAddress[regId] == 5  ) { chanLvl[5]      =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 18 ) { chanFreq[5]     =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 19 ) { chanPulseCnt[5] =dataSource[deviceId].value[regId]; }    

		// Deals with chan 6 value registers
		if ( dataSource[deviceId].regAddress[regId] == 6  ) { chanLvl[6]      =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 20 ) { chanFreq[6]     =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 21 ) { chanPulseCnt[6] =dataSource[deviceId].value[regId]; }    

		// Deals with chan 7 value registers
		if ( dataSource[deviceId].regAddress[regId] == 7  ) { chanLvl[7]      =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 22 ) { chanFreq[7]     =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 23 ) { chanPulseCnt[7] =dataSource[deviceId].value[regId]; }    

		// Deals with chan 8 value registers
		if ( dataSource[deviceId].regAddress[regId] == 8  ) { chanLvl[8]      =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 24 ) { chanFreq[8]     =dataSource[deviceId].value[regId]; }    
		if ( dataSource[deviceId].regAddress[regId] == 25 ) { chanPulseCnt[8] =dataSource[deviceId].value[regId]; }    
	} 
	
	
	
	// present the output in the format desired by the command line option
	if (displayType == HUMANREAD)
	{			
		printf("_____| DO8 Modbus Address %i |______________________________________________________________________\n", dataSource[deviceId].modbusId);
		printf("Ch\tMode\t\tLevel\t\tPulse Freq\tPulse Count\n");
        
        // see https://eecs.wsu.edu/~cs150/reading/printf.htm for futher information on printf formating 


        for(int chanNo=1 ; chanNo <9 ; chanNo++)
		{		
            printf("%i\t%-12s\t",chanNo, chMode[ dataSource[deviceId].ChanMode[chanNo] ]);

            if (dataSource[deviceId].ChanMode[chanNo]  < 2 )      // Level 
                printf("%-16i%-16s%-16s\n",chanLvl[chanNo],"-","-");
            else if (dataSource[deviceId].ChanMode[chanNo] > 1 )  // Pulse Count
			{
				if (chanFreq[chanNo] == 0)	
				{ 
					pulseFreqTemp = 0;	
				}
				else
				{
					pulseFreqTemp=((1.0/chanFreq[chanNo])*1000);
				}

                printf("%-16s%-16f%-16i\n","-", pulseFreqTemp,chanPulseCnt[chanNo]);
			}
        }

        printf("\n\n");       
	}	



	if (displayType == JSONREAD)
	{				
		printf ("      \"name\":\"RTU-DO8\",\n");
		printf ("      \"type\": %i,\n",dataSource[deviceId].deviceType);
		printf ("      \"deviceId\":\"%i\",\n",deviceId);
		printf ("      \"modbusId\":\"%i\",\n",dataSource[deviceId].modbusId);	        
		printf ("      \"channels\": 8,\n");

		for(int chanNo=1 ; chanNo <9 ; chanNo++)
		{				
			printf ("      \"chan %i\": {\n",chanNo);
			printf ("         \"mode\": %i,\n",dataSource[deviceId].ChanMode[chanNo]);
            if (dataSource[deviceId].ChanMode[chanNo]  < 2 )                 
                printf ("         \"Level\": %i\n",chanLvl[chanNo]);
            else if (dataSource[deviceId].ChanMode[chanNo]> 1 )
            {
				if (chanFreq[chanNo] == 0)
					 pulseFreqTemp = 0;
				else
					pulseFreqTemp=((1.0/chanFreq[chanNo])*1000);

			    printf ("         \"frequency\": %3.2f,\n", pulseFreqTemp);
			    printf ("         \"numPulse\": %i\n",chanPulseCnt[chanNo]);
            }

			if (chanNo <8) { printf ("      },\n"); } else  { printf ("      }\n"); }			
		}
				
	}

	if (displayType == CPUREAD)
	{	

		//deviceId,deviceType,modbusId,ChansTotal,ChanMode[1], chanLvl[1], chanFreq[1], chanPulseCnt[1]....ChanMode[8], chanLvl[8], chanFreq[8], chanPulseCnt[8]...	
		printf("%i,%i,%i,8",deviceId,dataSource[deviceId].deviceType,dataSource[deviceId].modbusId);
        
        for(int chanNo=1 ; chanNo <9 ; chanNo++)
		{				
		        printf (",%i,", dataSource[deviceId].ChanMode[chanNo]);
                printf ("%i,%3.2f,%i", (int)chanLvl[chanNo], ((1.0/chanFreq[chanNo])*1000), (int)chanPulseCnt[chanNo]);
                
		}
        printf(";\n");

	}

}
