//
// Created by 盧威任 on 5/1/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTUREORDER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTUREORDER_HPP
enum class StructureOrderType {
    NOT_CONSTRUCTED_YET,
    CONSTRUCTED,
    SELECTING_SITE,
    BUILT,
    NO_ORDER,
    TAKEN_DAMAGE
};
class StructureOrder {
public:
    StructureOrder() {}
    virtual ~StructureOrder() {}

    StructureOrderType getStructureOrderType() { return m_StructOrder; }

    void setStructureOrder(StructureOrderType structorder) {
        m_StructOrder = structorder;
    }

    bool getBuilt() {
        if (m_StructOrder == StructureOrderType::BUILT) {
            return true;
        } else {
            return false;
        }
    }

protected:
    StructureOrderType m_StructOrder;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTUREORDER_HPP
