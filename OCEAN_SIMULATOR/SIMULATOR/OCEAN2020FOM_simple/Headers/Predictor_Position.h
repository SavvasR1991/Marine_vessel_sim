#pragma once
#ifndef POSITION_PREDICTION_H
#define POSITION_PREDICTION_H
#include <iostream>

class Predictor_Position{

private:
	double P_init;
	double X[4]; 
	double P[4][4];
	double x; 
	double y;
	double R_;
	bool coutmess;

	void kalman_xy(double X[4], double P[4][4], double x, double y, double R_)
	{
		double Y1 = x - X[0];
		double Y2 = y - X[1];

		double dererminant = (P[0][0] + R_)*(P[1][1] + R_) - (P[1][0] + R_)*(P[0][1] + R_);
		double P11_i = (P[1][1] + R_) / dererminant;
		double P12_i = (-(P[0][1] + R_)) / dererminant;
		double P21_i = (-(P[1][0] + R_)) / dererminant;
		double P22_i = (P[0][0] + R_) / dererminant;

		double K11_ = P[0][0] * P11_i + P[0][1] * P21_i;
		double K12_ = P[0][0] * P12_i + P[0][1] * P22_i;
		double K21_ = P[1][0] * P11_i + P[1][1] * P21_i;
		double K22_ = P[1][0] * P12_i + P[1][1] * P22_i;
		double K31_ = P[2][0] * P11_i + P[2][1] * P21_i;
		double K32_ = P[2][0] * P12_i + P[2][1] * P22_i;
		double K41_ = P[3][0] * P11_i + P[3][1] * P21_i;
		double K42_ = P[3][0] * P12_i + P[3][1] * P22_i;

		double K11_H_P = (1.0 - K11_);
		double K12_H_P = (0.0 - K12_);
		double K13_H_P = (0.0);
		double K14_H_P = (0.0);
		double K21_H_P = (0.0 - K21_);
		double K22_H_P = (1.0 - K22_);
		double K23_H_P = (0.0);
		double K24_H_P = (0.0);
		double K31_H_P = (0.0 - K31_);
		double K32_H_P = (0.0 - K32_);
		double K33_H_P = (1.0);
		double K34_H_P = (0.0);
		double K41_H_P = (0.0 - K41_);
		double K42_H_P = (0.0 - K42_);
		double K43_H_P = (0.0);
		double K44_H_P = (1.0);

		double P11 = K11_H_P * P[0][0] + K12_H_P * P[1][0] + K13_H_P * P[2][0] + K14_H_P * P[3][0];
		double P12 = K11_H_P * P[0][1] + K12_H_P * P[1][1] + K13_H_P * P[2][1] + K14_H_P * P[3][1];
		double P13 = K11_H_P * P[0][2] + K12_H_P * P[1][2] + K13_H_P * P[2][2] + K14_H_P * P[3][2];
		double P14 = K11_H_P * P[0][3] + K12_H_P * P[1][3] + K13_H_P * P[2][3] + K14_H_P * P[3][3];
		double P21 = K21_H_P * P[0][0] + K22_H_P * P[1][0] + K23_H_P * P[2][0] + K24_H_P * P[3][0];
		double P22 = K21_H_P * P[0][1] + K22_H_P * P[1][1] + K23_H_P * P[2][1] + K24_H_P * P[3][1];
		double P23 = K21_H_P * P[0][2] + K22_H_P * P[1][2] + K23_H_P * P[2][2] + K24_H_P * P[3][2];
		double P24 = K21_H_P * P[0][3] + K22_H_P * P[1][3] + K23_H_P * P[2][3] + K24_H_P * P[3][3];
		double P31 = K31_H_P * P[0][0] + K32_H_P * P[1][0] + K33_H_P * P[2][0] + K34_H_P * P[3][0];
		double P32 = K31_H_P * P[0][1] + K32_H_P * P[1][1] + K33_H_P * P[2][1] + K34_H_P * P[3][1];
		double P33 = K31_H_P * P[0][2] + K32_H_P * P[1][2] + K33_H_P * P[2][2] + K34_H_P * P[3][2];
		double P34 = K31_H_P * P[0][3] + K32_H_P * P[1][3] + K33_H_P * P[2][3] + K34_H_P * P[3][3];
		double P41 = K41_H_P * P[0][0] + K42_H_P * P[1][0] + K43_H_P * P[2][0] + K44_H_P * P[3][0];
		double P42 = K41_H_P * P[0][1] + K42_H_P * P[1][1] + K43_H_P * P[2][1] + K44_H_P * P[3][1];
		double P43 = K41_H_P * P[0][2] + K42_H_P * P[1][2] + K43_H_P * P[2][2] + K44_H_P * P[3][2];
		double P44 = K41_H_P * P[0][3] + K42_H_P * P[1][3] + K43_H_P * P[2][3] + K44_H_P * P[3][3];

		double X1_Pr = X[0] + (K11_* Y1 + K12_ * Y1);
		double X2_Pr = X[1] + (K21_* Y1 + K22_ * Y2);
		double X3_Pr = X[2] + (K31_* Y1 + K32_ * Y2);
		double X4_Pr = X[3] + (K41_* Y1 + K42_ * Y2);

		X[0] = X1_Pr + X3_Pr;
		X[1] = X2_Pr + X4_Pr;
		X[2] = X3_Pr;
		X[3] = X4_Pr;

		double F11_P = P11 + P31;
		double F12_P = P12 + P32;
		double F13_P = P13 + P33;
		double F14_P = P14 + P34;
		double F21_P = P21 + P41;
		double F22_P = P22 + P42;
		double F23_P = P23 + P43;
		double F24_P = P24 + P44;
		double F31_P = P31;
		double F32_P = P32;
		double F33_P = P33;
		double F34_P = P34;
		double F41_P = P41;
		double F42_P = P42;
		double F43_P = P43;
		double F44_P = P44;

		P[0][0] = F11_P + F13_P + 1;
		P[0][1] = F12_P + F14_P;
		P[0][2] = F13_P;
		P[0][3] = F14_P;
		P[1][0] = F21_P + F23_P;
		P[1][1] = F22_P + F24_P + 1;
		P[1][2] = F23_P;
		P[1][3] = F24_P;
		P[2][0] = F31_P + F33_P;
		P[2][1] = F32_P + F34_P;
		P[2][2] = F33_P + 1;
		P[2][3] = F34_P;
		P[3][0] = F41_P + F43_P;
		P[3][1] = F42_P + F44_P;
		P[3][2] = F43_P;
		P[3][3] = F44_P + 1;

	}

public:
	
	Predictor_Position(double x, double y , double R_) {
		coutmess = false;
		this->P_init = 1000.0;
		for (int i = 0; i < 4; i++) {
			X[i] = 0.0;
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				P[i][j] = 0.0;
			}
		}

		P[0][0] = P_init;
		P[1][1] = P_init;
		P[2][2] = P_init;
		P[3][3] = P_init;
		this->x = x;
		this->y = y;
		this->R_ = R_;
	}

	Predictor_Position() {
		std::cout << "---- Position Prediction Creation" << std::endl;
		this->P_init = 1000.0;
		for (int i = 0; i < 4; i++) {
			X[i] = 0.0;
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				P[i][j] = 0.0;
			}
		}
		
		P[0][0] = P_init;
		P[1][1] = P_init;
		P[2][2] = P_init;
		P[3][3] = P_init;
		this->x = 0.0;
		this->y = 0.0;
		this->R_ = 0.0;
	}

	~Predictor_Position() {
		if(coutmess)
			std::cout << "---- Position Prediction Deleted" << std::endl;
	}

	void reset_kalman_filter() {
		this->P_init = 1000.0;
		for (int i = 0; i < 4; i++) {
			X[i] = 0.0;
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				P[i][j] = 0.0;
			}
		}
		
		P[0][0] = P_init;
		P[1][1] = P_init;
		P[2][2] = P_init;
		P[3][3] = P_init;
		this->x = 0.0;
		this->y = 0.0;
		this->R_ = 0.0;
	}

	void set_start_kalman_filter(double *x, double *y, double vessel_x, double vessel_y, double R_) {
		kalman_xy(X, P, vessel_x, vessel_y, R_);
		*x = this->X[0];
		*y = this->X[1];
	}

	void print_P() {
		cout << P[0][0] << " " << P[0][1] << " " << P[0][2] << " " << P[0][3] << endl;
		cout << P[1][0] << " " << P[1][1] << " " << P[1][2] << " " << P[1][3] << endl;
		cout << P[2][0] << " " << P[2][1] << " " << P[2][2] << " " << P[2][3] << endl;
		cout << P[3][0] << " " << P[3][1] << " " << P[3][2] << " " << P[3][3] << endl << endl;
	}

	void print_X() {
		cout << X[0] << " " << X[1] << " " << X[2] << " " << X[3] << endl<< endl;
	}

};

#endif