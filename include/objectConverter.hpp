#pragma once

#include <cstdlib>

#include "json.hpp"
#include "plant.h"
#include "log.h"

// for convenience
using json = nlohmann::json;

const std::string nameField = "name"; // string
const std::string amountField = "amount"; // int
const std::string valueField = "value"; // int
const std::string waterField = "water"; // int
const std::string frequencyField = "frequency"; // int
const std::string growTimeField = "grow_time"; // int

class MissedParameterException {
    public:
        std::string type;

        MissedParameterException(const std::string& type) : type {type} {};
};

class Converter {
    private:
        static int parceInt(const json& json, const std::string& fieldName, bool required)
        {
            try {
                return json.at(fieldName);
            } catch (std::out_of_range& e) {
                if (required) {
                    throw MissedParameterException(fieldName);
                }
            }

            return 0;
        };

        static std::string parceStr(const json& json, const std::string& fieldName, bool required)
        {
            try {
                return json.at(fieldName);
            } catch (std::out_of_range& e) {
                if (required) {
                    throw MissedParameterException(fieldName);
                }
            }

            return 0;
        };

        Converter() {};

    public:
        static Plant&& toPlant(const json& j)
        {
            std::string name{parceStr(j, nameField, true)};
            int value{parceInt(j, valueField, true)};
            int water{parceInt(j, waterField, true)};
            int frequency{parceInt(j, frequencyField, true)};
            int growTime{parceInt(j, growTimeField, true)};

            Plant p(name, value, water, frequency, growTime);

            return std::move(p);
        };

        static int toAmount(const json& j)
        {
            return parceInt(j, amountField, true);
        };

        static json toJson(const Plant& plant)
        {
            json j;

            j[nameField] = plant.getName();
            j[valueField] = plant.getValue();
            j[waterField] = plant.getConsumedWater();
            j[frequencyField] = plant.getFrequency();
            j[growTimeField] = plant.getGrowTime();

            j[amountField] = rand() % 10;

            return j;
        }
};