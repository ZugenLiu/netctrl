/* vim:set ts=4 sw=4 sts=4 et: */

#include <set>
#include <stdexcept>
#include <igraph/cpp/edge.h>
#include <igraph/cpp/generators/line_graph.h>
#include <netctrl/model/liu.h>
#include <netctrl/model/switchboard.h>

namespace netctrl {

using namespace igraph;

SwitchboardControllabilityModel::~SwitchboardControllabilityModel() {
    clearControlPaths();
}

void SwitchboardControllabilityModel::calculate() {
    // Construct the line graph first
    Graph lg(line_graph(*m_pGraph));

    // Find the driver nodes in the line graph; these are the driver edges
    // in our model
    LiuControllabilityModel model(&lg);
    model.calculate();
    
    // Loop through the stems and buds of the line graph. The root of each
    // stem represents an edge in the original graph and its tail will
    // become a driver node.
    std::vector<ControlPath*> controlPaths = model.controlPaths();
    std::set<long int> driverNodeSet;

    for (std::vector<ControlPath*>::const_iterator it = controlPaths.begin();
            it != controlPaths.end(); it++) {
        ControlPath* path = *it;
        Stem* stem = dynamic_cast<Stem*>(path);
        if (stem != 0) {
            // Store the source vertex of the root of the stem
            driverNodeSet.insert(m_pGraph->edge(stem->root()).tail());
        }
    }

    m_driverNodes = Vector(driverNodeSet.begin(), driverNodeSet.end());
}

void SwitchboardControllabilityModel::clearControlPaths() {
    for (std::vector<ControlPath*>::const_iterator it = m_controlPaths.begin();
            it != m_controlPaths.end(); it++) {
        delete *it;
    }
}

std::vector<ControlPath*> SwitchboardControllabilityModel::controlPaths() const {
    return m_controlPaths;
}

igraph::Vector SwitchboardControllabilityModel::driverNodes() const {
    return m_driverNodes;
}

}        // end of namespaces

