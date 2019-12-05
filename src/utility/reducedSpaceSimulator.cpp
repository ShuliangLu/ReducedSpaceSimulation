#include <iostream>
#include <config/ConfigFile.h>
#include <vector>
#define MAX_STR_LEN 128

// configuration
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

ConfigFile config;

typedef struct MeshSate{
    double *position;
    double *velocity;
    double *nodal_forces;
    unsigned int *tets;
    unsigned int dof_offset;
} MeshState;
std::vector<MeshState> sim_state;

// load the config data from configuration file
void initializeConfig(char *config_filename);
// interpret the configuration for rendering system
void initializeRenderingSystem();
// interpret the configuration for simulation system
void initializeSimulationSystem();
// simulate a frame
int simulateOneFrame(std::vector<MeshState> &sim_state);
// render a frame
int render(const std::vector<MeshState> &sim_state);
// processing user interactions
void processInteraction();


int close_app = false;
int pause_app = true;

int main(int argc,char *argv[])
{
    initializeConfig(argv[1]);
    config.printOptions();

    std::cout << "*******************THIS IS REDUCED SPACE SIMULATION PLATFORM*******************" << std::endl;
    initializeRenderingSystem();
    initializeSimulationSystem();

//    main-loop
    while(!close_app)
    {
        if(!pause_app) {
            render(sim_state);
            simulateOneFrame(sim_state);
        }
        processInteraction();
    }

    std::cout << "******************* close *******************" << std::endl;
    return 0;
}


void initializeConfig(char *config_filename)
{
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
}
