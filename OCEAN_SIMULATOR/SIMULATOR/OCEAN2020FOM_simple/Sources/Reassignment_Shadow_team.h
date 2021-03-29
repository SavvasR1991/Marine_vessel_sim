#pragma once
#ifndef REASSIGNMENT_SHADOW_TEAM_H
#define REASSIGNMENT_SHADOW_TEAM_H

#include "Data_Stuctures.h"
#include "General_functions.h"

namespace Reassignment_Shadow_Team  {

	/******************* shadow_team_reassignment_required *********************/
	bool shadow_team_reassignment_required(std::vector<SHADOWING_TEAM_DATA*> team_shadowing_summary, std::vector<TARGET_STATS> targets) {
		bool is_reassignment_required = false;
		int current_id = -1, minimum_members = 0;

		for (std::vector<TARGET_STATS>::iterator it = std::begin(targets); it != std::end(targets); ++it) {
			current_id = (it)->id;
			minimum_members = 0;
			for (std::vector<SHADOWING_TEAM_DATA*>::iterator it2 = std::begin(team_shadowing_summary); it2 != std::end(team_shadowing_summary); ++it2) {
				if ((*it2)->get_type() == "SURFACE") {
					if ((*it2)->get_id() == current_id) {
						minimum_members++;
					}
				}
				if (minimum_members < 2) {
					is_reassignment_required = true;
					break;
				}
			}
		}
		return is_reassignment_required;
	}

	bool is_vessel_reassignment_possible(std::map<std::string, SHADOWING_TEAM*> *teams_shawdowing, std::vector<SHADOWING_TEAM_DATA*> *team_shadowing_summary) {
		int free_members = 0;
		int possible_vangared_members = 0;
		for (std::vector<SHADOWING_TEAM_DATA*>::iterator itt = std::begin(*team_shadowing_summary); itt != std::end(*team_shadowing_summary); ++itt) {
			if ((*itt)->get_type() == "SURFACE") {
				if ((*itt)->is_available()) {
					free_members++;
				}
			}
		}
		for (std::map<std::string, SHADOWING_TEAM*>::iterator itt = std::begin(*teams_shawdowing); itt != std::end(*teams_shawdowing); ++itt) {
			if ((*itt).second->get_shadow_team()->size() == 3) {
				possible_vangared_members++;
			}
			else if ((*itt).second->get_shadow_team()->size() == 4) {
				possible_vangared_members++;
				possible_vangared_members++;
			}
		}
		if ((possible_vangared_members + free_members) >= 2) {
			return true;
		}
		else {
			return false;
		}
	}

	bool is_vessel_reassignment_possible_sub(std::map<std::string, SHADOWING_TEAM*> *teams_shawdowing, std::vector<SHADOWING_TEAM_DATA*> *team_shadowing_summary) {
		int free_members = 0;
		int possible_vangared_members = 0;
		for (std::vector<SHADOWING_TEAM_DATA*>::iterator itt = std::begin(*team_shadowing_summary); itt != std::end(*team_shadowing_summary); ++itt) {
			if ((*itt)->get_type() == "SUB_ROV") {
				if ((*itt)->is_available()) {
					free_members++;
				}
			}
		}
		for (std::map<std::string, SHADOWING_TEAM*>::iterator itt = std::begin(*teams_shawdowing); itt != std::end(*teams_shawdowing); ++itt) {
			if ((itt)->second->get_shadow_team()->at(0)->get_type() == "SUB_ROV") {
				if ((*itt).second->get_shadow_team()->size() == 2) {
					possible_vangared_members++;
				}
				else if ((*itt).second->get_shadow_team()->size() == 3) {
					possible_vangared_members++;
					possible_vangared_members++;
				}
				else if ((*itt).second->get_shadow_team()->size() == 4) {
					possible_vangared_members++;
					possible_vangared_members++;
					possible_vangared_members++;
				}
			}
		}
		if ((possible_vangared_members + free_members) >= 1) {
			return true;
		}
		else {
			return false;
		}
	}

	bool vessel_reassignment_check_if_one_is_available(std::map<std::string, SHADOWING_TEAM*> *teams_shawdowing) {
		for (std::map<std::string, SHADOWING_TEAM*>::iterator itt = std::begin(*teams_shawdowing); itt != std::end(*teams_shawdowing); ++itt) {
			if (((itt)->second->get_shadow_team())->size() > 2) {
				return true;
			}
		}
		return false;
	}

	bool vessel_reassignment_check_if_one_is_available_sub(std::map<std::string, SHADOWING_TEAM*> *teams_shawdowing) {
		for (std::map<std::string, SHADOWING_TEAM*>::iterator itt = std::begin(*teams_shawdowing); itt != std::end(*teams_shawdowing); ++itt) {
			if (((itt)->second->get_shadow_team())->size() >= 2) {
				return true;
			}
		}
		return false;
	}

	bool vessel_reassignment_check_if_two_are_available(std::map<std::string, SHADOWING_TEAM*> *teams_shawdowing) {
		int counter = 0;
		for (std::map<std::string, SHADOWING_TEAM*>::iterator itt = std::begin(*teams_shawdowing); itt != std::end(*teams_shawdowing); ++itt) {
			if (((itt)->second->get_shadow_team())->size() > 3) {
				return true;
			}
			else if (((itt)->second->get_shadow_team())->size() == 3) {
				counter++;
			}
			if (counter >= 2) {
				return true;
			}
		}
		return false;
	}

	bool vessel_reassignment_check_if_two_are_available_exact(std::map<std::string, SHADOWING_TEAM*> *teams_shawdowing) {
		int counter = 0;
		for (std::map<std::string, SHADOWING_TEAM*>::iterator itt = std::begin(*teams_shawdowing); itt != std::end(*teams_shawdowing); ++itt) {
			if (((itt)->second->get_shadow_team())->size() > 3) {
				return true;
			}
		}
		return false;
	}

	int vessel_reassignment_closest_team_one_vessel(std::map<std::string, SHADOWING_TEAM*> *teams_shawdowing, double x, double y, double z) {
		int id = 1;
		double distance = -1;
		double curr_distance = -1;
		for (std::map<std::string, SHADOWING_TEAM*>::iterator itt = std::begin(*teams_shawdowing); itt != std::end(*teams_shawdowing); ++itt) {
			if (((itt)->second->get_shadow_team())->size() >= 3) {
				curr_distance = point_distance(x, y, (itt)->second->get_shadow_team()->at(0)->get_X(), (itt)->second->get_shadow_team()->at(0)->get_Y());
				if (distance <= curr_distance) {
					id = (itt)->second->get_shadow_team()->at(0)->get_id();
				}
			}
		}
		return id;
	}

	int vessel_reassignment_closest_team_one_vessel_sub(std::map<std::string, SHADOWING_TEAM*> *teams_shawdowing, double x, double y, double z) {
		int id = 1;
		double distance = -1;
		double curr_distance = -1;
		for (std::map<std::string, SHADOWING_TEAM*>::iterator itt = std::begin(*teams_shawdowing); itt != std::end(*teams_shawdowing); ++itt) {
			if ((itt)->second->get_shadow_team()->at(0)->get_type() == "SUB_ROV") {
				if (((itt)->second->get_shadow_team())->size() >= 2) {
					curr_distance = point_distance(x, y, (itt)->second->get_shadow_team()->at(0)->get_X(), (itt)->second->get_shadow_team()->at(0)->get_Y());
					if (distance <= curr_distance) {
						id = (itt)->second->get_shadow_team()->at(0)->get_id();
					}
				}
			}
		}
		return id;
	}
	
	/******************* vessel_reassignment_performance ***********************/
	void vessel_reassignment_performance(std::map<std::string, SHADOWING_TEAM*> *teams_shawdowing, std::vector<SHADOWING_TEAM_DATA*> *team_shadowing_summary, std::vector<TARGET_STATS> targets, double refLatitude, double refLongitude, char comm) {
		int current_id = -1, minimum_members = 0, minimum_members_sub = 0, counter = 0;
		bool created;
		std::string new_leader, target_name, team_type;
		std::vector<SHADOWING_TEAM_DATA*> *candidate_team_with_one_extra_1 = NULL, *candidate_team_with_one_extra_2 = NULL, *candidate_team_with_one_extra = NULL;
		std::vector<TARGET_STATS> unmatched_targets;

		for (std::vector<TARGET_STATS>::iterator it = std::begin(targets); it != std::end(targets); ++it) {
			current_id = (it)->id;
			minimum_members = 0;
			for (std::vector<SHADOWING_TEAM_DATA*>::iterator it2 = std::begin(*team_shadowing_summary); it2 != std::end(*team_shadowing_summary); ++it2) {
				if ((*it2)->get_type() == "SURFACE") {
					if ((*it2)->get_id() == current_id) {
						minimum_members++;
					}
				}
			}
			if (minimum_members < 2) {
				unmatched_targets.push_back(TARGET_STATS((it)->x, (it)->y, (it)->z, (it)->vel, (it)->ang, (it)->radius, (it)->id));
			}
		}
		for (std::vector<TARGET_STATS>::iterator it = std::begin(unmatched_targets); it != std::end(unmatched_targets); ++it) {
			target_name = "Surface_Target_" + to_string((it)->id);
			team_type = "SURFACE";
			if (is_vessel_reassignment_possible(teams_shawdowing, team_shadowing_summary)) {
				std::vector<SHADOWING_TEAM_DATA*> free_vessels;
				for (std::vector<SHADOWING_TEAM_DATA*>::iterator it_summ = std::begin(*team_shadowing_summary); it_summ != std::end(*team_shadowing_summary); ++it_summ) {
					if ((*it_summ)->get_type() == "SURFACE") {
						if ((*it_summ)->is_available()) {
							free_vessels.push_back(new SHADOWING_TEAM_DATA(0, (*it_summ)->get_Radar_Range(), (*it_summ)->get_name(), (*it_summ)->get_type(), "no_leader", false, 0, (*it_summ)->get_radius(), counter, JOB::VANGUARED, 'n'));
						}
					}
				}
				if (free_vessels.size() >= 2) {
					teams_shawdowing->insert(std::pair<std::string, SHADOWING_TEAM*>(target_name, new SHADOWING_TEAM()));
					created = (*teams_shawdowing)[target_name]->create_new_shadow_team((it)->x, (it)->y, (it)->z, (it)->id, 2, *team_shadowing_summary, team_type, comm);
					if (!created) {
						teams_shawdowing->erase(target_name);
					}
				}
				else if (free_vessels.size() == 1) {
					if (vessel_reassignment_check_if_one_is_available(teams_shawdowing)) {
						int id_candidate = vessel_reassignment_closest_team_one_vessel(teams_shawdowing, (it)->x, (it)->y, (it)->z);
						for (std::map<std::string, SHADOWING_TEAM*>::iterator itt = std::begin(*teams_shawdowing); itt != std::end(*teams_shawdowing); ++itt) {
							candidate_team_with_one_extra = ((itt)->second->get_shadow_team());
							if (candidate_team_with_one_extra->at(0)->get_id() == id_candidate) {
								break;
							}
							else {
								candidate_team_with_one_extra = NULL;
							}
						}
						if (candidate_team_with_one_extra != NULL) {
							int index = 0;
							for (std::vector<SHADOWING_TEAM_DATA*>::iterator itt = std::begin(*candidate_team_with_one_extra); itt != std::end(*candidate_team_with_one_extra); ++itt) {
								if (!((*itt)->is_leader())) {
									for (std::vector<SHADOWING_TEAM_DATA*>::iterator it_summ = std::begin(*team_shadowing_summary); it_summ != std::end(*team_shadowing_summary); ++it_summ) {
										if ((*it_summ)->get_type() == "SURFACE") {
											if ((*itt)->get_name() == (*it_summ)->get_name()) {
												(*it_summ)->set_availability(true);
												(*it_summ)->set_vessel_name_leader("no_leader");
												(*it_summ)->set_job(JOB::PATROLING);
												(*it_summ)->set_id(0);
												(*it_summ)->set_shadow_id(0);
												(*it_summ)->set_coord_BeforeRotation(0, 0, 0);
												break;
											}
										}
									}
									(*candidate_team_with_one_extra).erase((*candidate_team_with_one_extra).begin() + index);
									int possition = 0;
									for (std::vector<SHADOWING_TEAM_DATA*>::iterator ittt = std::begin(*candidate_team_with_one_extra); ittt != std::end(*candidate_team_with_one_extra); ++ittt) {
										(*ittt)->set_shadow_id(possition);
										possition++;
									}
									break;
								}
								index++;
							}
							teams_shawdowing->insert(std::pair<std::string, SHADOWING_TEAM*>(target_name, new SHADOWING_TEAM()));
							created = (*teams_shawdowing)[target_name]->create_new_shadow_team((it)->x, (it)->y, (it)->z, (it)->id, 2, *team_shadowing_summary, team_type, comm);
							if (!created) {
								teams_shawdowing->erase(target_name);
							}
						}
					}
				}
				else {
					int index = 0, possition = 0, curr_id = 0;
					if (vessel_reassignment_check_if_two_are_available(teams_shawdowing)) {
						if (vessel_reassignment_check_if_two_are_available_exact(teams_shawdowing)) {
							for (std::map<std::string, SHADOWING_TEAM*>::iterator itt = std::begin(*teams_shawdowing); itt != std::end(*teams_shawdowing); ++itt) {
								candidate_team_with_one_extra_1 = ((itt)->second->get_shadow_team());
								if (candidate_team_with_one_extra_1 != NULL) {
									if ((*candidate_team_with_one_extra_1).size() == 4) {
										for (int i = 0; i < 2; i++) {
											index = 0;
											candidate_team_with_one_extra_1 = ((itt)->second->get_shadow_team());
											for (std::vector<SHADOWING_TEAM_DATA*>::iterator itt_cand = std::begin(*candidate_team_with_one_extra_1); itt_cand != std::end(*candidate_team_with_one_extra_1); ++itt_cand) {
												if (!((*itt_cand)->is_leader())) {
													for (std::vector<SHADOWING_TEAM_DATA*>::iterator it_summ = std::begin(*team_shadowing_summary); it_summ != std::end(*team_shadowing_summary); ++it_summ) {
														if ((*it_summ)->get_type() == "SURFACE") {
															if ((*itt_cand)->get_name() == (*it_summ)->get_name()) {
																(*it_summ)->set_availability(true);
																(*it_summ)->set_vessel_name_leader("no_leader");
																(*it_summ)->set_id(0);
																(*it_summ)->set_job(JOB::PATROLING);
																(*it_summ)->set_shadow_id(0);
																(*it_summ)->set_coord_BeforeRotation(0, 0, 0);
																break;
															}
														}
													}
													(*candidate_team_with_one_extra_1).erase((*candidate_team_with_one_extra_1).begin() + index);
													possition = 0;
													for (std::vector<SHADOWING_TEAM_DATA*>::iterator ittt2 = std::begin(*candidate_team_with_one_extra_1); ittt2 != std::end(*candidate_team_with_one_extra_1); ++ittt2) {
														(*ittt2)->set_shadow_id(possition);
														possition++;
													}
													break;
												}
												index++;
											}
										}
									}
								}
							}
						}
						else {
							for (std::map<std::string, SHADOWING_TEAM*>::iterator itt = std::begin(*teams_shawdowing); itt != std::end(*teams_shawdowing); ++itt) {
								candidate_team_with_one_extra_1 = ((itt)->second->get_shadow_team());
								if (candidate_team_with_one_extra_1 != NULL) {
									if ((*candidate_team_with_one_extra_1).size() == 3) {
										curr_id = (candidate_team_with_one_extra_1)->at(0)->get_id();
										break;
									}
								}
							}
							for (std::map<std::string, SHADOWING_TEAM*>::iterator itt = std::begin(*teams_shawdowing); itt != std::end(*teams_shawdowing); ++itt) {
								candidate_team_with_one_extra_2 = ((itt)->second->get_shadow_team());
								if (candidate_team_with_one_extra_2 != NULL) {
									if ((*candidate_team_with_one_extra_2).size() == 3) {
										if ((candidate_team_with_one_extra_2)->at(0)->get_id() != curr_id) {
											break;
										}
									}
								}
							}
							if (candidate_team_with_one_extra_1 != NULL && candidate_team_with_one_extra_2 != NULL) {
								for (int i = 0; i < 2; i++) {
									index = 0;
									for (std::vector<SHADOWING_TEAM_DATA*>::iterator itt_cand = std::begin(*candidate_team_with_one_extra_1); itt_cand != std::end(*candidate_team_with_one_extra_1); ++itt_cand) {
										if (!((*itt_cand)->is_leader())) {
											for (std::vector<SHADOWING_TEAM_DATA*>::iterator it_summ = std::begin(*team_shadowing_summary); it_summ != std::end(*team_shadowing_summary); ++it_summ) {
												if ((*it_summ)->get_type() == "SURFACE") {
													if ((*itt_cand)->get_name() == (*it_summ)->get_name()) {
														(*it_summ)->set_availability(true);
														(*it_summ)->set_vessel_name_leader("no_leader");
														(*it_summ)->set_id(0);
														(*it_summ)->set_job(JOB::PATROLING);
														(*it_summ)->set_shadow_id(0);
														(*it_summ)->set_coord_BeforeRotation(0, 0, 0);
														break;
													}
												}
											}
											(*candidate_team_with_one_extra_1).erase((*candidate_team_with_one_extra_1).begin() + index);
											possition = 0;
											for (std::vector<SHADOWING_TEAM_DATA*>::iterator ittt2 = std::begin(*candidate_team_with_one_extra_1); ittt2 != std::end(*candidate_team_with_one_extra_1); ++ittt2) {
												(*ittt2)->set_shadow_id(possition);
												possition++;
											}
											break;
										}
										index++;
									}
									candidate_team_with_one_extra_1 = candidate_team_with_one_extra_2;
								}
							}
						}
						teams_shawdowing->insert(std::pair<std::string, SHADOWING_TEAM*>(target_name, new SHADOWING_TEAM()));
						created = (*teams_shawdowing)[target_name]->create_new_shadow_team((it)->x, (it)->y, (it)->z, (it)->id, 2, *team_shadowing_summary, team_type, comm);
						if (!created) {
							teams_shawdowing->erase(target_name);
						}
					}
				}
			}
			counter++;
		}
		unmatched_targets.clear();

	}
	
	void vessel_reassignment_performance_sub(std::map<std::string, SHADOWING_TEAM*> *teams_shawdowing, std::vector<SHADOWING_TEAM_DATA*> *team_shadowing_summary, std::vector<TARGET_STATS> targets, double refLatitude, double refLongitude, char comm) {
		int current_id = -1, minimum_members = 0, minimum_members_sub = 0, counter = 0;
		bool created;
		std::string new_leader, target_name, team_type;
		std::vector<SHADOWING_TEAM_DATA*> *candidate_team_with_one_extra_1 = NULL, *candidate_team_with_one_extra_2 = NULL, *candidate_team_with_one_extra = NULL;
		std::vector<TARGET_STATS> unmatched_targets_subwater;

		for (std::vector<TARGET_STATS>::iterator it = std::begin(targets); it != std::end(targets); ++it) {
			current_id = (it)->id;
			minimum_members_sub = 0;
			for (std::vector<SHADOWING_TEAM_DATA*>::iterator it2 = std::begin(*team_shadowing_summary); it2 != std::end(*team_shadowing_summary); ++it2) {
				if ((*it2)->get_type() == "SUB_ROV") {
					if ((*it2)->get_id() == current_id) {
						minimum_members_sub++;
					}
				}
			}
			if (minimum_members_sub < 1) {
				unmatched_targets_subwater.push_back(TARGET_STATS((it)->x, (it)->y, (it)->z, (it)->vel, (it)->ang, (it)->radius, (it)->id));
			}
		}
		candidate_team_with_one_extra = NULL;
		for (std::vector<TARGET_STATS>::iterator it = std::begin(unmatched_targets_subwater); it != std::end(unmatched_targets_subwater); ++it) {
			target_name = "Surface_Target_" + to_string((it)->id);
			team_type = "SUB_ROV";
			if (is_vessel_reassignment_possible_sub(teams_shawdowing, team_shadowing_summary)) {
				std::vector<SHADOWING_TEAM_DATA*> free_vessels;
				for (std::vector<SHADOWING_TEAM_DATA*>::iterator it_summ = std::begin(*team_shadowing_summary); it_summ != std::end(*team_shadowing_summary); ++it_summ) {
					if ((*it_summ)->get_type() == "SUB_ROV") {
						if ((*it_summ)->is_available()) {
							free_vessels.push_back(new SHADOWING_TEAM_DATA(0, (*it_summ)->get_Radar_Range(), (*it_summ)->get_name(), (*it_summ)->get_type(), "no_leader", false, 0, (*it_summ)->get_radius(), counter, JOB::VANGUARED, 'n'));
						}
					}
				}
				if (free_vessels.size() >= 1) {
					teams_shawdowing->insert(std::pair<std::string, SHADOWING_TEAM*>(target_name, new SHADOWING_TEAM()));
					created = (*teams_shawdowing)[target_name]->create_new_shadow_team((it)->x, (it)->y, (it)->z, (it)->id, 2, *team_shadowing_summary, team_type, comm);
					if (!created) {
						teams_shawdowing->erase(target_name);
					}
				}
				else {
					if (vessel_reassignment_check_if_one_is_available_sub(teams_shawdowing)) {
						for (std::map<std::string, SHADOWING_TEAM*>::iterator itt = std::begin(*teams_shawdowing); itt != std::end(*teams_shawdowing); ++itt) {
							if ((itt)->second->get_shadow_team()->at(0)->get_type() == "SUB_ROV") {
								if ((itt)->second->get_shadow_team()->size() > 1) {
									candidate_team_with_one_extra = ((itt)->second->get_shadow_team());
									break;
								}
								else {
									candidate_team_with_one_extra = NULL;
								}
							}
						}

						if (candidate_team_with_one_extra != NULL) {
							int index = 0;
							for (std::vector<SHADOWING_TEAM_DATA*>::iterator itt = std::begin(*candidate_team_with_one_extra); itt != std::end(*candidate_team_with_one_extra); ++itt) {
								if (!((*itt)->is_leader())) {
									for (std::vector<SHADOWING_TEAM_DATA*>::iterator it_summ = std::begin(*team_shadowing_summary); it_summ != std::end(*team_shadowing_summary); ++it_summ) {
										if ((*it_summ)->get_type() == "SUB_ROV") {
											if ((*itt)->get_name() == (*it_summ)->get_name()) {
												(*it_summ)->set_availability(true);
												(*it_summ)->set_vessel_name_leader("no_leader");
												(*it_summ)->set_job(JOB::PATROLING);
												(*it_summ)->set_id(0);
												(*it_summ)->set_shadow_id(0);
												(*it_summ)->set_coord_BeforeRotation(0, 0, 0);
												break;
											}
										}
									}
									(*candidate_team_with_one_extra).erase((*candidate_team_with_one_extra).begin() + index);
									int possition = 0;
									for (std::vector<SHADOWING_TEAM_DATA*>::iterator ittt = std::begin(*candidate_team_with_one_extra); ittt != std::end(*candidate_team_with_one_extra); ++ittt) {
										(*ittt)->set_shadow_id(possition);
										possition++;
									}
									break;
								}
								index++;
							}
							teams_shawdowing->insert(std::pair<std::string, SHADOWING_TEAM*>(target_name, new SHADOWING_TEAM()));
							created = (*teams_shawdowing)[target_name]->create_new_shadow_team((it)->x, (it)->y, (it)->z, (it)->id, 2, *team_shadowing_summary, team_type, comm);
							if (!created) {
								teams_shawdowing->erase(target_name);
							}
						}
					}
				}
			}
			counter++;
		}
		unmatched_targets_subwater.clear();
	}
}

#endif