//
// Created by shuliang on 2019/12/5.
//

#include <config/ConfigFile.h>
#include <iostream>
#include <string>

#include <cstdio>
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getced
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif


std::string GetCurretnWorkingDir(void) {
    char buff[FILENAME_MAX];
    GetCurrentDir(buff, FILENAME_MAX);
    std::string current_working_dir(buff);
    return current_working_dir;
}

#define MAX_STR_LEN 128

char example_name_str[MAX_STR_LEN];
char model_filename_str[MAX_STR_LEN];
bool using_latentspace_dynamics;
char latentspace_network_name[MAX_STR_LEN];
double gravity;
char elastic_model_str[MAX_STR_LEN];
double density;
double young_modulus;
double poisson_ratio;
double damping_mass_coef;
double damping_stiff_coef;
char solver_str[MAX_STR_LEN];
bool using_reducedspace_dynamics;
int nbasis;
bool using_cubature;
char cubature_filename[MAX_STR_LEN];

double time_step;
unsigned int max_iter;
double tolerence;

bool simulate_contact;
char contact_model_str[MAX_STR_LEN];
double volume_contact_ratio;

bool recording_video;
unsigned int num_frames;
double simulation_time;
bool recording_trace;
unsigned int num_traces_record;

int main(int argc,char *argv[])
{
    std::cout << "working_dir : " << GetCurretnWorkingDir() << std::endl;

    ConfigFile config;
    config.addOption("example_name",example_name_str);
    config.addOption("model_filename",model_filename_str);
    config.addOption("using_latent_space_dynamics",&using_latentspace_dynamics);
    config.addOption("latent_space_network_name",latentspace_network_name);
    config.addOption("gravity",&gravity);
    config.addOption("elastic_model",elastic_model_str);
    config.addOption("density",&density);
    config.addOption("young_modulus",&young_modulus);
    config.addOption("poisson_ratio",&poisson_ratio);
    config.addOption("damping_mass_coef",&damping_mass_coef);
    config.addOption("damping_stiff_coef",&damping_stiff_coef);
    config.addOption("solver",solver_str);
    config.addOption("using_reduced_space_dynamics",&using_reducedspace_dynamics);
    config.addOption("nbasis",&nbasis);
    config.addOption("using_cubature",&using_cubature);
    config.addOption("cubature_filename",cubature_filename);
    config.addOption("time_step",&time_step);
    config.addOption("max_iter",&max_iter);
    config.addOption("tolerence",&tolerence);
    config.addOption("simulate_contact",&simulate_contact);
    config.addOption("contact_model",contact_model_str);
    config.addOption("volume_contact_ratio",&volume_contact_ratio);
    config.addOption("recording_video",&recording_video);
    config.addOption("num_frames",&num_frames);
    config.addOption("simulation_time",&simulation_time);
    config.addOption("recording_trace",&recording_trace);
    config.addOption("num_traces_record",&num_traces_record);

    config.parseOptions("../../example/HC_RLL.json",1,JSON_FORMAT);
    config.printOptions();
    return 0;
}
