#ifndef CONOR_STATISTICS_HPP
#define CONOR_STATISTICS_HPP

#include <string>

namespace conor
{

struct Statistics
{
    Statistics(std::string &stats_path);
    Statistics(std::string &&stats_path);

    int curr_health{};
    int max_health{};
    int speed{};
    int atack{};
    int defence{};
};

}

#endif // CONOR_STATS_H
