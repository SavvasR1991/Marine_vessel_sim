#pragma once
#ifndef TARGET_H
#define TARGET_H

#include "OCEAN_Federates_Headers.h"

class Target{

private:
	DtTime dt;
	double x;
	double y;
	double z;
	double vel;
	double velx;
	double vely;

	double ax;
	double ay;

	double angle_hor;
	double angle_ver;
	std::string name;
	std::string type;
	std::string logs;
	bool flag;
	double mass;
	double l;
	double w;
	double h;
	double ref_x;
	double ref_y;
	double origine_angle;

	int type_id = 222;
	int id;
	int turning_probability;
	int cycleCounter;

	int target_turning_point_1;
	int target_turning_point_2;
	int target_turning_point_3;
	int target_turning_point_4;
	int target_turning_point_5;
	int target_turning_point_6;
	int target_turning_point_7;
	int target_turning_point_8;
	int target_turning_point_9;
	int target_turning_point_10;
	double target_turning_angle;

	DtOCEAN2020EntityStateRepository* VesselDataSR;
	DtEntityPublisher* VesselDataPub;
	DtTopoView* VesselDataTopoView;
	DtVector32 final_acceleration;
	DtDcm final_geocToLocalRot;
	DtVector32 final_velocity;
	DtVector final_possition;
	DtTaitBryan final_orient;
	DtExerciseConn* exConn;

public:
	
	Target(DtExerciseConn* con, std::string nam, std::string type, double x, double y, double z, double v, double a, double aa, DtTime dt, int id, int t, std::string logs,double ref_x,double ref_y) {
		double psi = DtDeg2Rad(a);

		this->flag = true;
		this->dt = dt;
		this->x = x;
		this->y = y;
		this->z = z;
		this->name = nam;
		this->type = type;
		this->vel = v;
		this->velx = v * cos(psi);
		this->vely = v * sin(psi);

		this->ax = 0.0;
		this->ay = 0.0;
		this->angle_hor = a;
		angle_degree_normalization(this->angle_hor);
		this->origine_angle = this->angle_hor;

		this->ref_x = ref_x;
		this->ref_y = ref_y;

		this->angle_ver = aa;
		this->exConn = con;	
		this->l = 4;
		this->w = 2;
		this->h = 2;
		this->id = id;
		this->logs = logs;
		this->turning_probability = t;
		int type_id = 0;

		this->target_turning_point_1 = 1;
		this->target_turning_point_2 = 1;
		this->target_turning_point_3 = 1;
		this->target_turning_point_4 = 1;
		this->target_turning_point_5 = 1;
		this->target_turning_point_6 = 1;
		this->target_turning_point_7 = 1;
		this->target_turning_point_8 = 1;
		this->target_turning_point_9 = 1;
		this->target_turning_point_10 = 1;
		this->target_turning_angle = -1;

		print_color_message("\n------- New Target creation " + name + " ------------------\n", COLOR_TEXT::MAIN_TITLE_RED);
		print_color_message("---- Publisher\n", COLOR_TEXT::CYAN_COLOR);
		cout << "------> MarkingText";
		print_color_message(": " + this->name + "_EKPA_RED\n", COLOR_TEXT::ORANGE_COLOR);
		if (this->type == "SURFACE") {
			std::cout << "------> EntityType";
			print_color_message(" : 1:3:82:19:0:0:82\n", COLOR_TEXT::ORANGE_COLOR);
			type_id = 1000;
		}
		else {
			std::cout << "------> EntityType";
			print_color_message(" : 1:4:82:8:1:0:1\n", COLOR_TEXT::ORANGE_COLOR);
			type_id = 1005;
		}
		std::cout << "------> EntityId";
		print_color_message("   : " + to_string(this->type_id) + ":" + to_string(type_id) + ":" + to_string(this->id) + "\n", COLOR_TEXT::ORANGE_COLOR);
		std::cout << "------> DtForce";
		print_color_message("    : Opposining\n", COLOR_TEXT::ORANGE_COLOR);


		if (type == "SUB_ROV") {
			if (this->exConn != NULL) {
				if (turning_probability<=1) {


					DtEntityType SubmersibleVesselDataType(1, 4, 82, 8, 1, 0, 1); //1:4:82:8:1:0:1
					this->VesselDataPub = new DtEntityPublisher(SubmersibleVesselDataType, this->exConn, DtDrDrmRvw, DtForceOpposing, DtEntityPublisher::guiseSameAsType());

					this->VesselDataSR = (DtOCEAN2020EntityStateRepository*)VesselDataPub->esr();
					this->VesselDataSR->setForceId(DtForceOpposing);
					this->VesselDataSR->setAlgorithm(DtDeadReckonTypes::DtDrDrmRvw);
					this->VesselDataSR->setGuise(SubmersibleVesselDataType);
					this->VesselDataSR->setEntityType(SubmersibleVesselDataType);
					this->VesselDataSR->setMarkingText((this->name + "_NKUA_RED").c_str());
					this->VesselDataSR->setEntityId(DtEntityIdentifier(this->type_id, this->type_id, this->id));
					this->VesselDataSR->setDimensionLength(l);
					this->VesselDataSR->setDimensionWidth(w);
					this->VesselDataSR->setDimensionHeight(h);

					this->VesselDataTopoView = new DtTopoView(VesselDataSR, DtDeg2Rad(ref_x), DtDeg2Rad(ref_y));

					this->final_possition[0] = (x);
					this->final_possition[1] = (y);
					this->final_possition[2] = (z);

					this->final_orient = DtTaitBryan(DtDeg2Rad(angle_hor), DtDeg2Rad(0.0), DtDeg2Rad(0.0));

					this->final_velocity[0] = 0.0;
					this->final_velocity[1] = 0.0;
					this->final_velocity[2] = 0.0;

					this->final_acceleration[0] = 0.0;
					this->final_acceleration[1] = 0.0;
					this->final_acceleration[2] = 0.0;

					this->VesselDataTopoView->setAcceleration(this->final_acceleration);
					this->VesselDataTopoView->setLocation(this->final_possition);
					this->VesselDataTopoView->setOrientation(this->final_orient);
					this->VesselDataTopoView->setVelocity(this->final_velocity);

					std::cout << "---- Location  " << VesselDataTopoView->location() << std::endl;
					std::cout << "---- Publisher " << VesselDataSR->location() << std::endl;
				}
				else {
					DtEntityType SubmersibleVesselDataType(1, 4, 0, 8, 15, 0, 0); //1:4:82:8:1:0:1
					this->VesselDataPub = new DtEntityPublisher(SubmersibleVesselDataType, this->exConn, DtDrDrmRvw, DtForceOpposing, DtEntityPublisher::guiseSameAsType());

					this->VesselDataSR = (DtOCEAN2020EntityStateRepository*)VesselDataPub->esr();
					this->VesselDataSR->setForceId(DtForceOpposing);
					this->VesselDataSR->setAlgorithm(DtDeadReckonTypes::DtDrDrmRvw);
					this->VesselDataSR->setGuise(SubmersibleVesselDataType);
					this->VesselDataSR->setEntityType(SubmersibleVesselDataType);
					this->VesselDataSR->setMarkingText((this->name + "_NKUA_RED").c_str());
					this->VesselDataSR->setEntityId(DtEntityIdentifier(this->type_id, this->type_id, this->id));
					this->VesselDataSR->setDimensionLength(l);
					this->VesselDataSR->setDimensionWidth(w);
					this->VesselDataSR->setDimensionHeight(h);

					this->VesselDataTopoView = new DtTopoView(VesselDataSR, DtDeg2Rad(ref_x), DtDeg2Rad(ref_y));

					this->final_possition[0] = (x);
					this->final_possition[1] = (y);
					this->final_possition[2] = (z);

					this->final_orient = DtTaitBryan(DtDeg2Rad(angle_hor), DtDeg2Rad(0.0), DtDeg2Rad(0.0));

					this->final_velocity[0] = 0.0;
					this->final_velocity[1] = 0.0;
					this->final_velocity[2] = 0.0;

					this->final_acceleration[0] = 0.0;
					this->final_acceleration[1] = 0.0;
					this->final_acceleration[2] = 0.0;

					this->VesselDataTopoView->setAcceleration(this->final_acceleration);
					this->VesselDataTopoView->setLocation(this->final_possition);
					this->VesselDataTopoView->setOrientation(this->final_orient);
					this->VesselDataTopoView->setVelocity(this->final_velocity);
				}
			}
			else {
				this->VesselDataPub = NULL;
			}
		}
		else {
			if (this->exConn != NULL) {
				if (this->exConn != NULL) {
					DtEntityType SurfaceVesselDataType(1, 3, 82, 19, 0, 0, 82);	 //1:3:82:19:0:0:82
					this->VesselDataPub = new DtEntityPublisher(SurfaceVesselDataType, this->exConn, DtDrDrmRvw, DtForceOpposing, DtEntityPublisher::guiseSameAsType());

					this->VesselDataSR = (DtOCEAN2020EntityStateRepository*)VesselDataPub->esr();
					this->VesselDataSR->setForceId(DtForceOpposing);
					this->VesselDataSR->setAlgorithm(DtDeadReckonTypes::DtDrDrmRvw);
					this->VesselDataSR->setGuise(SurfaceVesselDataType);
					this->VesselDataSR->setEntityType(SurfaceVesselDataType);
					this->VesselDataSR->setMarkingText((this->name).c_str());
					this->VesselDataSR->setEntityId(DtEntityIdentifier(this->type_id, this->type_id, this->id));
					this->VesselDataSR->setDimensionLength(l);
					this->VesselDataSR->setDimensionWidth(w);
					this->VesselDataSR->setDimensionHeight(h);

					this->VesselDataTopoView = new DtTopoView(VesselDataSR, DtDeg2Rad(ref_x), DtDeg2Rad(ref_y));

					this->final_possition[0] = (x);
					this->final_possition[1] = (y);
					this->final_possition[2] = 0.0; 

					this->final_orient = DtTaitBryan(DtDeg2Rad(angle_hor), DtDeg2Rad(0.0), DtDeg2Rad(0.0));

					this->final_velocity[0] = 0.0;
					this->final_velocity[1] = 0.0;
					this->final_velocity[2] = 0.0;

					this->final_acceleration[0] = 0.0;
					this->final_acceleration[1] = 0.0;
					this->final_acceleration[2] = 0.0;

					this->VesselDataTopoView->setAcceleration(this->final_acceleration);
					this->VesselDataTopoView->setLocation(this->final_possition);
					this->VesselDataTopoView->setOrientation(this->final_orient);
					this->VesselDataTopoView->setVelocity(this->final_velocity);
				}
			}
			else {
				this->VesselDataPub = NULL;
			}
		}
		
	}
	~Target() {
		std::cout << "\n>>----- " << name << " Deleted -----<<" << std::endl;
	}
	
	void set_turning_status(int target_turning_point_1,int target_turning_point_2,int target_turning_point_3,int target_turning_point_4,int target_turning_point_5,int target_turning_point_6,int target_turning_point_7,int target_turning_point_8,int target_turning_point_9,int target_turning_point_10,	double target_turning_angle) {

		this->target_turning_point_1 = target_turning_point_1;
		this->target_turning_point_2 = target_turning_point_2;
		this->target_turning_point_3 = target_turning_point_3;
		this->target_turning_point_4 = target_turning_point_4;
		this->target_turning_point_5 = target_turning_point_5;
		this->target_turning_point_6 = target_turning_point_6;
		this->target_turning_point_7 = target_turning_point_7;
		this->target_turning_point_8 = target_turning_point_8;
		this->target_turning_point_9 = target_turning_point_9;
		this->target_turning_point_10 = target_turning_point_10;
		this->target_turning_angle = target_turning_angle;
	}

	double get_x() {
		return this->x;
	}
	double get_y() {
		return this->y;
	}
	double get_z() {
		return this->z;
	}
	double get_vel() {
		return this->vel;
	}
	double get_angle_hor() {
		return this->angle_hor;
	}
	int get_id() {
		return id;
	}
	int get_turning_probability() {
		return this->turning_probability;
	}
	
	void VesselsimTick(DtTime dt_team, DtTime dtt) {
		if (this->turning_probability > 1) {
			
			if (this->turning_probability >= dt_team) {
				double psi = DtDeg2Rad(angle_hor);
			
				x = x + (velx + 0.5 * ax * dtt) *dtt;
				y = y + (vely + 0.5 * ay * dtt) *dtt;

				velx = (velx + ax * dtt);
				vely = (vely + ay * dtt);

				vel = sqrt(pow(velx, 2) + pow(vely, 2));

			}
			else {
				if (flag) {
					print_color_message("\n------- MINE Detected " + name + " ------------------\n", COLOR_TEXT::MAIN_TITLE_RED);
					flag = false;
				}
				this->final_possition[0] = (this->x);
				this->final_possition[1] = (this->y);
				this->final_possition[2] = (this->z);

				this->final_orient = DtTaitBryan(DtDeg2Rad(angle_degree_normalization(0.0)), DtDeg2Rad(0.0), DtDeg2Rad(0.0));

				this->final_velocity[0] = 0.0; //In km per hour
				this->final_velocity[1] = 0.0; //In km per hour
				this->final_velocity[2] = 0.0;

				this->final_acceleration[0] = 0.0;
				this->final_acceleration[1] = 0.0;
				this->final_acceleration[2] = 0.0;

				if (this->type != "SURFACE") {
					this->final_possition[2] = -this->z;
				}

				if (this->exConn != NULL) {
					try {

						this->VesselDataTopoView->setAcceleration(this->final_acceleration);
						this->VesselDataTopoView->setOrientation(this->final_orient);
						this->VesselDataTopoView->setLocation(this->final_possition);
						this->VesselDataTopoView->setVelocity(this->final_velocity);

						this->VesselDataPub->tick();
					}
					catch (std::exception e) {
					}
				}
			}
			std::fstream target_income;
			target_income.open(this->logs + "\\Target_" + to_string(id) + ".txt", std::fstream::in | std::fstream::out | std::fstream::app);
			target_income << this->cycleCounter << " [" << setprecision(12) << (this->final_possition[0]) << ", " << setprecision(12) << (this->final_possition[1]) << ", " << setprecision(12) << z << "]\n";
			target_income.close();
	

		}
		else {
			
			if (dt_team < 2000) {

				if (dt_team == target_turning_point_1) {
					this->angle_hor = angle_degree_normalization(this->angle_hor + target_turning_angle);
					this->origine_angle = this->angle_hor;
				}
				if (dt_team == target_turning_point_2) {
					this->angle_hor = angle_degree_normalization(this->angle_hor + target_turning_angle);
					this->origine_angle = this->angle_hor;

				}
				if (dt_team == target_turning_point_3) {
					this->angle_hor = angle_degree_normalization(this->angle_hor + target_turning_angle);
					this->origine_angle = this->angle_hor;

				}
				if (dt_team == target_turning_point_4) {
					this->angle_hor = angle_degree_normalization(this->angle_hor + target_turning_angle);
					this->origine_angle = this->angle_hor;

				}
				if (dt_team == target_turning_point_5) {
					this->angle_hor = angle_degree_normalization(this->angle_hor + target_turning_angle);
					this->origine_angle = this->angle_hor;

				}
				if (dt_team == target_turning_point_6) {
					this->angle_hor =angle_degree_normalization( this->angle_hor + target_turning_angle);
					this->origine_angle = this->angle_hor;

				}
				if (dt_team == target_turning_point_7) {
					this->angle_hor = angle_degree_normalization(this->angle_hor + target_turning_angle);
					this->origine_angle = this->angle_hor;

				}
				if (dt_team == target_turning_point_8) {
					this->angle_hor = angle_degree_normalization(this->angle_hor + target_turning_angle);
					this->origine_angle = this->angle_hor;

				}
				if (dt_team == target_turning_point_9) {
					this->angle_hor = angle_degree_normalization(this->angle_hor + target_turning_angle);
					this->origine_angle = this->angle_hor;

				}
				double psi = DtDeg2Rad(angle_hor);

				this->velx = vel * cos(psi);
				this->vely = vel * sin(psi);


				x = x + (velx + 0.5 * ax * dtt) *dtt;
				y = y + (vely + 0.5 * ay * dtt) *dtt;

				velx = (velx + ax * dtt);
				vely = (vely + ay * dtt);

				vel = sqrt(pow(velx, 2) + pow(vely, 2));
			}
			else {
				velx = 0.0;
				vely = 0.0;
				vel = 0.0;
			}
			this->final_possition[0] = (this->x);
			this->final_possition[1] = (this->y);
			this->final_possition[2] = (this->z);

			this->final_orient = DtTaitBryan(DtDeg2Rad(angle_degree_normalization(this->angle_hor)), DtDeg2Rad(0.0), DtDeg2Rad(0.0));

			this->final_velocity[0] = velx; //In km per hour
			this->final_velocity[1] = vely; //In km per hour
			this->final_velocity[2] = 0.0;

			this->final_acceleration[0] = ax;
			this->final_acceleration[1] = ay;
			this->final_acceleration[2] = 0.0;

			if (this->type != "SURFACE") {
				this->final_possition[2] = -this->z;
			}

			if (this->exConn != NULL) {
				try {

					//this->VesselDataTopoView->setAcceleration(this->final_acceleration);
					this->VesselDataTopoView->setOrientation(this->final_orient);
					this->VesselDataTopoView->setLocation(this->final_possition);
					//this->VesselDataTopoView->setVelocity(this->final_velocity);

					this->VesselDataPub->tick();

					std::fstream target_income;
					target_income.open(this->logs + "\\Target_" + to_string(id) + ".txt", std::fstream::in | std::fstream::out | std::fstream::app);
					target_income << this->cycleCounter << " [" << setprecision(12) << (this->final_possition[0]) << ", " << setprecision(12) << (this->final_possition[1]) << ", " << setprecision(12) << z << "]\n";
					target_income.close();
				}
				catch (std::exception e) {
				}
			}
		}

	}
};

#endif