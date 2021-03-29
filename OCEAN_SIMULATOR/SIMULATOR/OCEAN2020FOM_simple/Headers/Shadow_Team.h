#pragma once
#ifndef SHADOWING_TEAM_H
#define SHADOWING_TEAM_H

#include <matrix/3dPoint.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <stdexcept>


struct Comparison
{
	bool const operator()(SHADOWING_TEAM_DATA *lhs, SHADOWING_TEAM_DATA *rhs) const
	{
return (*lhs).get_distance() < (*rhs).get_distance();
	}
};

class SHADOWING_TEAM {

private:

	int team_shadow_number;
	int target_number;

	double x_t;
	double y_t;
	double z_t;

	char comment;
	vector<SHADOWING_TEAM_DATA*> shadow_teams;

	std::string leader;
	std::string type;

public:

	SHADOWING_TEAM() {
	}

	~SHADOWING_TEAM() {
		for (std::vector<SHADOWING_TEAM_DATA*>::iterator it = std::begin(this->shadow_teams); it != std::end(this->shadow_teams); ++it) {
			delete (*it);
		}
	}

	bool create_new_shadow_team(double x, double y, double z, int id, int num_shadows, vector<SHADOWING_TEAM_DATA*> &vessel_array, std::string type, char comm) {
		double distance;
		int total_available_vessel = 0, diff = 0, i = 0;
		int min_vessel_num = 0;

		this->target_number = id;
		this->comment = comm;
		this->team_shadow_number = num_shadows;
		this->x_t = x;
		this->y_t = y;
		this->z_t = z;
		this->type = type;
		this->leader = "NO";

		if (type == "SURFACE") {
			min_vessel_num = 2;
		}
		else {
			if (z >= 0) {
				return false;
			}
			min_vessel_num = 1;
		}
		for (std::vector<SHADOWING_TEAM_DATA*>::iterator it = std::begin(vessel_array); it != std::end(vessel_array); ++it) {
			if ((*it)->is_available()) {
				if ((*it)->get_type() == type) {
					if (type == "SURFACE") {
						distance = point_distance((*it)->get_X(), (*it)->get_Y(), x, y);
					}
					else {
						distance = point_distance_3d((*it)->get_X(), (*it)->get_Y(), (*it)->get_Z(), x, y, z);
					}
					shadow_teams.push_back(new SHADOWING_TEAM_DATA(distance, (*it)->get_Radar_Range(), (*it)->get_name(), type, (*it)->get_vessel_name_leader(), false, 0, (*it)->get_radius(), id, JOB::VANGUARED, 'n'));
					total_available_vessel++;
				}
			}
		}

		if (total_available_vessel >= min_vessel_num) {
			sort(this->shadow_teams.begin(), this->shadow_teams.end(), Comparison());
			if (total_available_vessel >= this->team_shadow_number) {
				diff = int(this->shadow_teams.size()) - int(this->team_shadow_number);
			}
			else {
				diff = int(this->shadow_teams.size()) - int(total_available_vessel);
			}
			if (this->shadow_teams.size() >= diff) {
				this->shadow_teams.resize(this->shadow_teams.size() - diff);
			}
			this->shadow_teams[0]->vote_leader(true);
			this->shadow_teams[0]->set_vessel_name_leader(this->shadow_teams[0]->get_name());
			std::string leader_name = this->shadow_teams[0]->get_name();
			int shadow_team_id = 0;
			for (std::vector<SHADOWING_TEAM_DATA*>::iterator it2 = std::begin(this->shadow_teams); it2 != std::end(this->shadow_teams); ++it2) {
				(*it2)->set_vessel_name_leader(leader_name);
				(*it2)->set_id(id);
				(*it2)->set_job(JOB::VANGUARED);
				(*it2)->set_availability(false);
				(*it2)->set_coord_BeforeRotation(x, y, 0);
				(*it2)->set_shadow_id(shadow_team_id);
				shadow_team_id++;
				for (std::vector<SHADOWING_TEAM_DATA*>::iterator it = std::begin(vessel_array); it != std::end(vessel_array); ++it) {
					if ((*it2)->get_name() == (*it)->get_name()) {
						(*it)->set_availability(false);
						(*it)->set_vessel_name_leader(leader_name);
						(*it)->set_id(id);
						(*it)->set_job(JOB::VANGUARED);
						(*it)->set_shadow_id((*it2)->get_shadow_id());
						(*it)->set_coord_BeforeRotation(x, y, 0);
						this->leader = leader_name;
					}
				}
			}
			if (comm == 'y') {
				std::cout << "---- Shadow team Voted Creation surface: " << id << std::endl;
			}
			return true;
		}
		else {
			shadow_teams.clear();
			return false;
		}
	}

	void update_target_to_team(double xt, double yt, double zt, double vt, double tt, std::map<std::string, TEAM_JOB_STATUS*> team_status, vector<SHADOWING_TEAM_DATA*> &vessel_array, char comment) {
		double x, y, z;
		this->x_t = xt;
		this->y_t = yt;
		this->z_t = zt;
		this->comment = comment;
		if (!this->shadow_teams.empty()) {
			if (comment == 'y') {
				std::cout << "---- Update Shadow team Voted: {" << this->get_shadow_team_target_id() << "} with leader: " << this->shadow_teams[0]->get_vessel_name_leader() << std::endl;
			}
			for (std::vector<SHADOWING_TEAM_DATA*>::iterator it = std::begin(this->shadow_teams); it != std::end(this->shadow_teams); ++it) {
				x = (team_status[(*it)->get_name()])->current_latitude;
				y = (team_status[(*it)->get_name()])->current_longitude;
				z = (team_status[(*it)->get_name()])->current_Height;
				for (std::vector<SHADOWING_TEAM_DATA*>::iterator it2 = std::begin(vessel_array); it2 != std::end(vessel_array); ++it2) {
					if ((*it2)->get_name() == (*it)->get_name()) {
						(*it2)->update_shadow_member(x, y, z, xt, yt, zt, vt, tt);
					}
				}
				(*it)->update_shadow_member(x, y, z, xt, yt, zt, vt, tt);
			}
		}
	}

	void remove_shadow_member(int shadow_team_id) {
		int index = 0;
		for (std::vector<SHADOWING_TEAM_DATA*>::iterator it = std::begin(this->shadow_teams); it != std::end(this->shadow_teams); ++it) {
			if ((*it)->get_shadow_id() == shadow_team_id && (*it)->get_name() != (*it)->get_vessel_name_leader()) {
				(this->shadow_teams).erase((this->shadow_teams).begin() + index);
				break;
			}
			index++;
		}
	}

	void add_shadow_member(double distance,double radar, std::string name, std::string type, std::string leader, int id, double radius,int shadow_id) {
		(this->shadow_teams).push_back(new SHADOWING_TEAM_DATA(distance, radar, name, type, leader, false, id, radius, shadow_id, JOB::VANGUARED, 'n'));
		((this->shadow_teams).back())->update_shadow_member_target(this->x_t,this->y_t,this->z_t);
	}

	int get_shadow_team_target_id() {
		return this->target_number;
	}

	std::string get_leader() {
		return this->leader;
	}
	
	std::string get_type() {
		return this->type;
	}

	void print_shadow_teams() {
		int count = 1;
		std::cout << "---- Print shadow team "<<this->type <<" \n";
		if (!this->shadow_teams.empty()) {
			std::cout << "------- Team { " << this->shadow_teams[0]->get_id() << "} with leader: " << this->shadow_teams[0]->get_vessel_name_leader() << "\n";
			std::cout << "------- Team Target: { " << this->shadow_teams[0]->get_X_target() << ", " << this->shadow_teams[0]->get_Y_target() << "}\n";
			for (std::vector<SHADOWING_TEAM_DATA*>::iterator it = std::begin(this->shadow_teams); it != std::end(this->shadow_teams); ++it) {
				std::cout << "--------- node { " << to_string(count) << "} with distance:" << (*it)->get_distance() << " -> " << (*it)->get_name() << ", shadow_id:" << (*it)->get_shadow_id() << "\n";
				std::cout << "---------------- { " << (*it)->get_X_target() << " ," << (*it)->get_Y_target() << "} : (" << (*it)->get_X() << "," << (*it)->get_Y() << ")\n";
				count++;
			}
		}
	}

	vector<SHADOWING_TEAM_DATA*>* get_shadow_team() {
		return &(this->shadow_teams);
	}

};

#endif