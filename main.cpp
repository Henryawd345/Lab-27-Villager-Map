#include <iostream>
#include <map>
#include <tuple>
#include <vector>
using namespace std;

using VillagerData = tuple<int, string, string>;
using VillagerMap  = map<string, VillagerData>;

void printAll(const VillagerMap& m) {
    cout << "Villager details:\n";
    for (const auto& [name, data] : m) {
        const auto& [friendship, species, catchphrase] = data;
        cout << name << " [" << friendship << ", " << species << ", "
             << "\"" << catchphrase << "\"]\n";
    }
    cout << endl;
}



int main() {
    VillagerMap villagers;

    villagers["Audie"] = VillagerData{6, "Wolf", "Yippee!!"};
    villagers["Raymond"] = make_tuple(8, "Cat", "Awesome!!");
    villagers.insert({"Marshal", VillagerData{7, "Squirrel", "Noooo!!"}});

    if (auto it = villagers.find("Raymond"); it != villagers.end()) {
        auto& [f, s, c] = it->second;
        cout << "Access: Raymond -> friendship=" << f
             << ", species=" << s
             << ", catchphrase=\"" << c << "\"\n\n";
    }

    printAll(villagers);

    return 0;
}