void Read_Configuration_file(std::string configuration_file_path, std::vector<std::pair<std::string, std::string>> &file_data);
void Assign_global_variables(std::vector<std::pair<std::string, std::string>> &configuration_file_data);
void Create_and_initialize_csv(std::ofstream &Humain_contamine, std::ofstream &Humain_genomeAP, std::ofstream &Humain_genomeH, std::ofstream &Humain_hx, std::ofstream &Humain_hy, std::ofstream &Humain_immune);
void Open_append_mode_csv(std::ofstream &Humain_contamine, std::ofstream &Humain_genomeAP, std::ofstream &Humain_genomeH, std::ofstream &Humain_hx, std::ofstream &Humain_hy, std::ofstream &Humain_immune);