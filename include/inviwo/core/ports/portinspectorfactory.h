#ifndef IVW_PORTINSPECTORFACTORY_H
#define IVW_PORTINSPECTORFACTORY_H

#include <inviwo/core/common/inviwocoredefine.h>
#include <inviwo/core/common/inviwo.h>
#include <inviwo/core/util/inviwofactorybase.h>
#include <inviwo/core/util/singleton.h>
#include <inviwo/core/ports/portinspector.h>

namespace inviwo {

class IVW_CORE_API PortInspectorFactory
    : public Factory
    , public Singleton<PortInspectorFactory> {
        
public:
    PortInspectorFactory();
    virtual ~PortInspectorFactory(){}
                
    virtual void initialize();
    virtual void deinitialize(){};

    virtual PortInspector* getPortInspectorForPortClass(std::string className);
      
    typedef std::map<std::string, PortInspector*> PortInspectorMap;
        
 private:
    void registerPortInspector(PortInspector* portInspector);
    
    virtual IvwSerializable* create(std::string className) const { return 0; }
    virtual bool isValidType(std::string className) const {return false; }
        
    PortInspectorMap portInspectors_;

};

} // namespace

#endif // IVW_PORTINSPECTORFACTORY_H
