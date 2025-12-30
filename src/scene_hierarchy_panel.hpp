#include "singleton.hpp"
#include "scenes/scene.hpp"

namespace Lab
{

    class CSceneHierarchyPanel : public Utils::CSingleton<CSceneHierarchyPanel>
    {
    public:
        friend Utils::CSingleton<CSceneHierarchyPanel>;

        void SetSceneContext(const CScene &context) { m_Context = context; };
        // write scene move constructor
        // for m : models
        // new arr.emplace_back(m);

        void OnImGuiRender();

    private:
        CScene m_Context;
    };

} // namespace Lab
