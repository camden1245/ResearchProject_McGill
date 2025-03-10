//maincode.cpp
/* Notes - Camden da Silva (2025-03-06, 12:39)
**working file for code for spin coating process. 
**currently includes the code for controlling linear stage. 
**in the end, will contain code for control of all processes of spin coating process

**parts used:
linear stage:    https://www.amazon.ca/gp/product/B09N3HXN6R/ref=ewc_pr_img_5?smid=A3E9T3KQ1YPBBY&th=1
arduino uno r3:  https://www.amazon.ca/gp/product/B008GRTSV6/ref=ewc_pr_img_4?smid=A2748KFO7F9SYK&psc=1
stepper driver:  https://www.amazon.ca/Stepper-Controller-Engraving-Machine-Microstep/dp/B07KCBJ31Z/ref=sr_1_2_sspa?dib=eyJ2IjoiMSJ9.yZece018xLxhev9IT6DxQVlyMAQJOGuTuWn86lQY88GT_vsvawBWg2HvoY3vqK76_mHcxYoa6ErI1yLzI_0f5gIhO5IWwSrPF4dPQdUF-Wy7K6n-qUuNeTs7a6_W0eC5h5cPKV8ABYWkDXn14-BQV-7qNsQtjhbJgCnGnCvCkDObF2NhTvPCpmCjXI8YJZwrgeZJTam9ffW5siU63t3X13gcRHX2Fr-TQBfJmdvRIllYiF9XMpcZFNOCWqBs53g3imw41T0JgnkBjPAqyuFcblWjF3QU1jJDx-Vpg2puNgA.fRFTlWTwmYdc_21t_t7UzXA5Fb9cVia5W922YQwHU9I&dib_tag=se&keywords=tb6600&qid=1741282917&sr=8-2-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1
limit switch:    https://www.amazon.ca/DUTTY-ME-8108-Momentary-Switch-Roller/dp/B0CWGZRHPX/ref=sr_1_1_sspa?crid=34CKYPGAIZOB8&dib=eyJ2IjoiMSJ9.8e5l7HiICcDYU4sLZs4jIdpnh8BAgdjCtiinlVqQlNlPF4RKbjPbz0MTFPNPkRJGFsPSumDNResUAtu1W2LUGQtnb2zTJ2PbAxgQU7HUiCVPOmxuCRFWiEF_CuGwMEx8EIVQzL536c24aAF3R7Ggvdg9HDGwtNoX_J9st9T8ZcSdMXBIhPnhOWBUYcK6OXmtrc6JNGxyeNbS0NbRZxgcI_mLZlpbskg5cXMVJoGk6N8qikSXtkBs-mwv38Xy5fqn_pOCXNfC4Z_LMr1_JjK-MIAT4IwhLzNkUEhgqD11QvU.tgePB21-1YQRynucQHim1hqJBQwZ6ju8ro-e97GT7kg&dib_tag=se&keywords=momentary+ac+limit+switch+roller+lever+cnc+mill+laser+plasma&qid=1741283073&sprefix=momentary+ac+limit+switch+roller+lever+cnc+mill+laser+plasma%2Caps%2C90&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1
*/

#include "settings.h"
#include "linear_stage_control.h"
#include "motor_control.h"

#include <accelstepper.h>
#include <servo.h>

void setup(){
	linearStage_Setup();
	motorSetup();
}
void loop(){
	
	if (homedStatus != homed){
		homeStage();
	}
	else {
		spinCoatingRoutine();
		delay(2000)
	}
	delay(2000);
	
}
void spinCoatingRoutine(){
	for (int i = 0; i<numberOfLayers;i++){
		stepper.moveTo(positionA);
		stepper.runtoposition();
		//while (stepper.distanceToGo != 0 ){
		//	stepper.run();
		//}
		motorRoutine();
		//delay(spinCoatingTime);
		delay(2000);
		stepper.moveTo(positionB);
		stepper.runtoposition() // test the precision of thics~!
		//while (stepper.distanceToGo != 0){
		//	stepper.run();
		//}
		motorRoutine();
		//delay(spinCoatingTime);
		delay(2000);
	}
}
