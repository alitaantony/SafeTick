#include <Seeed_Arduino_SSCMA.h>

SSCMA AI;

void setup()
{
    AI.begin();
    Serial.begin(9600);
}

void loop()

{
    if (!AI.invoke())
    {
        for (int i = 0; i < AI.boxes().size(); i++)
        {
            int target = AI.boxes()[i].target;
            float score = AI.boxes()[i].score;

            // Check if confidence is greater than 50%
            if (score > 50.0 && target == 0) // Assuming target '0' is elephant
            {
                Serial.println("This is an elephant");
                return; // Exit the loop to avoid further processing
            }
        }

        // Optionally check for class-based confidence if required
        for (int i = 0; i < AI.classes().size(); i++)
        {
            int target = AI.classes()[i].target;
            float score = AI.classes()[i].score;

            if (score > 50.0 && target == 0) // Assuming target '0' is elephant
            {   
                
                Serial.println("This is an elephant");
                return; // Exit the loop to avoid further processing
            }
        }
    }
    delay(100); // Add a delay to prevent excessive looping
}
    
