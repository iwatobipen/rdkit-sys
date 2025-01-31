#include "rust/cxx.h"
#include "GraphMol/GraphMol.h"

namespace RDKit {
    std::shared_ptr<RWMol> rw_mol_from_ro_mol(std::shared_ptr<ROMol> mol, bool quick_copy, int conf_id) {
        RWMol *rw_mol = new RWMol(*mol, quick_copy, conf_id);
        return std::shared_ptr<RWMol>(rw_mol);
    }

    std::shared_ptr<RWMol> rw_mol_from_rw_mol(std::shared_ptr<RWMol> mol) {
        RWMol *rw_mol = new RWMol(*mol);
        return std::shared_ptr<RWMol>(rw_mol);
    }
}