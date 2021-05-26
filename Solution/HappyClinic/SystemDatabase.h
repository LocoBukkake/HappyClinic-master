#pragma once

#include <vector>
#include "Expert.h"
#include "Doctor.h"
#include "Patient.h"

class SystemDatabase
{
public:
   SystemDatabase() {};
   std::vector<Expert> experts;
   std::vector<Doctor> doctors;
   std::vector<Patient> patients;
};
