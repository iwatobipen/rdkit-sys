#include <vector>

#include "rust/cxx.h"
#include "GraphMol/GraphMol.h"
#include "GraphMol/MolStandardize/Tautomer.h"
#include "GraphMol/MolStandardize/Charge.h"

namespace RDKit {
    using ROMol = RDKit::ROMol;
    using TautomerEnumerator = MolStandardize::TautomerEnumerator;
    using TautomerEnumeratorResult = MolStandardize::TautomerEnumeratorResult;
    using CleanupParameters = MolStandardize::CleanupParameters;
    using Uncharger = MolStandardize::Uncharger;

    std::shared_ptr<TautomerEnumerator> tautomer_enumerator() {
        TautomerEnumerator *enumerator = new MolStandardize::TautomerEnumerator(new MolStandardize::TautomerCatalog());
        return std::shared_ptr<TautomerEnumerator>(enumerator);
    }

    std::shared_ptr<TautomerEnumeratorResult> tautomer_enumerate(std::shared_ptr<TautomerEnumerator> enumerator, std::shared_ptr<ROMol> mol) {
        TautomerEnumeratorResult stacked_enumerator = enumerator->enumerate(*mol);
        TautomerEnumeratorResult *heaped_enumerator = new TautomerEnumeratorResult(stacked_enumerator);
        return std::shared_ptr<TautomerEnumeratorResult>(heaped_enumerator);
    }

    int tautomer_enumerator_result_tautomers_size(std::shared_ptr<TautomerEnumeratorResult> enumerator_result) {
        return enumerator_result->size();
    }

    std::shared_ptr<ROMol> tautomer_enumerator_result_tautomers_at(std::shared_ptr<TautomerEnumeratorResult> enumerator_result, size_t at) {
        RDKit::ROMOL_SPTR sptr = enumerator_result->at(at);
        return std::shared_ptr<ROMol>(new ROMol(*sptr));
    }

    std::shared_ptr<ROMol> tautomer_enumerator_pick_canonical(std::shared_ptr<TautomerEnumerator> enumerator, std::shared_ptr<TautomerEnumeratorResult> enumerator_result) {
        ROMol *mol = enumerator->pickCanonical(*enumerator_result);
        return std::shared_ptr<ROMol>(mol);
    }

    std::shared_ptr<CleanupParameters> default_cleanup_parameters() {
        CleanupParameters *heap_cp = new CleanupParameters(MolStandardize::defaultCleanupParameters);
        return std::shared_ptr<CleanupParameters>(heap_cp);
    }

    std::shared_ptr<Uncharger> new_uncharger(bool canonical) {
        return std::shared_ptr<Uncharger>(new Uncharger(canonical));
    }

    std::shared_ptr<ROMol> uncharger_uncharge(std::shared_ptr<Uncharger> uncharger, std::shared_ptr<ROMol> mol) {
        ROMol *return_mol = uncharger->uncharge(*mol);
        return std::shared_ptr<ROMol>(return_mol);
    }

    std::shared_ptr<RWMol> fragment_parent(std::shared_ptr<RWMol> rw_mol, std::shared_ptr<CleanupParameters> cleanup_params, bool skip_standardize) {
        RWMol *parent = RDKit::MolStandardize::fragmentParent(*rw_mol, *cleanup_params, skip_standardize);
        return std::shared_ptr<RWMol>(parent);
    }

    std::shared_ptr<RWMol> normalize(std::shared_ptr<RWMol> mol, std::shared_ptr<CleanupParameters> cleanup_params) {
        RWMol *normalized = RDKit::MolStandardize::normalize(&*mol, *cleanup_params);
        return std::shared_ptr<RWMol>(normalized);
    }
}