/* vim:set ts=4 sw=4 sts=4 et: */

#ifndef NETCTRL_MODEL_LIU_H
#define NETCTRL_MODEL_LIU_H

#include <netctrl/model/controllability.h>

namespace netctrl {

/// Controllability model of Liu et al
class LiuControllabilityModel : public ControllabilityModel {
private:
    /// The list of driver nodes that was calculated
    igraph::Vector m_driverNodes;

    /// The list of control paths that was calculated
    std::vector<ControlPath*> m_controlPaths;

public:
    /// Constructs a model that will operate on the given graph
    LiuControllabilityModel(igraph::Graph* pGraph = 0)
        : ControllabilityModel(pGraph), m_driverNodes(), m_controlPaths() {
    }

    /// Destroys the model
    virtual ~LiuControllabilityModel();

    virtual void calculate();
    virtual std::vector<ControlPath*> controlPaths() const;
    virtual igraph::Vector driverNodes() const;

protected:
    /// Removes all the control paths from the previous run (if any)
    void clearControlPaths();
};

}       // end of namespace

#endif  // NETCTRL_MODEL_LIU_H

