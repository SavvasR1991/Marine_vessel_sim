#pragma once

/*
////////////////////////////////////////////////////////////////
///						INITIALIZATION						  //
////////////////////////////////////////////////////////////////
			   ________________|______________________
			   |			   |					  |
////////////////////////////   |			////////////////////////////
//	Set listen connection //   |			//	Set talk connection   //
////////////////////////////   | 			////////////////////////////	
							   |
							   |
							  \|/
				/////////////////////////////////
				///			SET FOMS		  //
				////////////////////////////////
			   ________________|______________________
			   |			   |					  |
////////////////////////////   |			////////////////////////////
//	Set listen FOMS		  //   |			//	Set talk connection   //
//		-AIR			  //   |			//		-RadioTransmiter  //
//		-LAND			  //   |			////////////////////////////
//		-WATERCOLM		  //   |
//		-WATERSURFACE	  //   |
////////////////////////////   | 	
							   |
							   |
							  \|/
				/////////////////////////////////
				///		  CREATE TEAM 		  //
				////////////////////////////////
			   ________________|
			   |			   |					  
////////////////////////////   |			
//	CREATE TEAM 		  //   |			
//		-VESSEL 1		  //   |			
//		-VESSEL 2		  //   |			
//		-.....			  //   |
//		-VESSEL n		  //   |
////////////////////////////   |
							   |
							  \|/
////////////////////////////////////////////////////////////////
///						START SIMULATION					  //
////////////////////////////////////////////////////////////////
							   |
	-------------------------->|
	|						   |
	|			///////////////////////////////// ----> Listen for AIR
	|			///			 LISTEN			   // ----> Listen for LAND	
	|			///////////////////////////////// ----> Listen for WATER COLMN
	|						   |				  ----> Listen for WATERSURFACE
	|						   |				  ----> Listen for EVENT
	| REPEAT				   |
	|						   |
	|						  \|/
	|			///////////////////////////////// ----> Evaluate EVENT
	|			///			 TALK    		  //  ----> MOVE VESSELS
	|			////////////////////////////////  ----> PUBLISH POSSITIONS
	|___________________________|				  ----> PUBLISH RADIOTRANSMITER
					            |
								|
							   \|/
////////////////////////////////////////////////////////////////
///					STOP SIMULATION	AND CLEANUP				  //
////////////////////////////////////////////////////////////////































*/
