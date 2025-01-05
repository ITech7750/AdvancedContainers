#ifndef LABA4_BUILDLOGISTICUNDIRECTEDGRAPHFROMFILEUSECASE_H
#define LABA4_BUILDLOGISTICUNDIRECTEDGRAPHFROMFILEUSECASE_H

#include <fstream>
#include "../data/Road.h"
#include "../data/City.h"
#include "../../../domain/model/UndirectedGraph.h"

class BuildLogisticUndirectedGraphFromFileUseCase {
public:
    s_UndirectedGraph<Road, City> operator()(String filePath) {
        s_UndirectedGraph g = s_UndirectedGraph<Road, City>();
        std::ifstream file(filePath);

        constexpr size_t bufferSize = 512 * 512;
        char *buffer(new char[bufferSize]);
        String currentPart;
        int openVPos = -1;
        int closeVPos = -1;
        while (file) {
            file.read(buffer, bufferSize);
            currentPart.append(buffer, file.gcount());
            while (std::count(currentPart.begin(), currentPart.end(), '{') > 0 && std::count(currentPart.begin(), currentPart.end(), '}') > 0) {
                if (openVPos == -1) {
                    if (std::count(currentPart.begin(), currentPart.end(), '{') != 0) {
                        openVPos = currentPart.find('{');
                    } else {

                    }
                }
                if (closeVPos == -1) {
                    if (std::count(currentPart.begin(), currentPart.end(), '}') != 0) {
                        closeVPos = currentPart.find('}');
                    }
                }
                if (openVPos != -1 && closeVPos != -1) {
                    String data = currentPart.substr(openVPos + 1, closeVPos - openVPos - 1);
                    currentPart = currentPart.substr(closeVPos + 1);

                    String r = data.substr(0, data.find(';'));
                    data = data.substr(data.find(';') + 1);
                    Road road = getRoadFromString(r);

                    String c1 = data.substr(0, data.find(';'));
                    data = data.substr(data.find(';') + 1);
                    City city1 = getCityFromString(c1);

                    String c2 = data.substr(0, data.find(';'));
                    City city2 = getCityFromString(c2);
                    openVPos = -1;
                    closeVPos = -1;

                    g.addTo(city1, city2, road);
                }
            }

        }
        return g;
    }
};

#endif //LABA4_BUILDLOGISTICUNDIRECTEDGRAPHFROMFILEUSECASE_H
