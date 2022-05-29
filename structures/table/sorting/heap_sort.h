#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"
#include "../../../Kriterium/CriterionObec.h"

namespace structures
{
	/// <summary> Triedenie Heap sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T, typename R>
	class HeapSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Heap sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table, bool vzostupne) override;
        void sortWithCriterion(UnsortedSequenceTable<K,T>& table, bool vzostupne, CriterionObec<R>& criterion);
	};

	template<typename K, typename T, typename R>
    inline void HeapSort<K, T, R>::sort(UnsortedSequenceTable<K, T>& table, bool vzostupne)
    {
        bool vymena = false;
        int aktualny;
        for (int i = 1; i <= table.size() - 1; i++)
        {
            aktualny = i;
            do {
                vymena = false;
                int otec = (aktualny - 1) / 2;
                if (vzostupne) {
                    if (aktualny > 0 && table.getItemAtIndex(aktualny).getKey() > table.getItemAtIndex(otec).getKey()){
                        table.swap(aktualny, otec);
                        aktualny = otec;
                        vymena = true;
                    }
                }
                else {
                    if (aktualny > 0 && table.getItemAtIndex(aktualny).getKey() < table.getItemAtIndex(otec).getKey()) {
                        table.swap(aktualny,otec);
                        aktualny = otec;
                        vymena = true;
                    }
                }
            } while (vymena);
        }
        int max;
        for (int i = table.size() - 1; i >= 1; i--)
        {
            table.swap(0, i);
            aktualny = 0;
            do {
                vymena = false;
                int lavy = aktualny * 2 + 1;
                int pravy = aktualny * 2 + 2;
                if (lavy < i && pravy < i) {
                    if (vzostupne) {
                        max = table.getItemAtIndex(lavy).getKey() > table.getItemAtIndex(pravy).getKey() ? lavy : pravy;
                    } else {
                        max = table.getItemAtIndex(lavy).getKey() < table.getItemAtIndex(pravy).getKey() ? lavy : pravy;
                    }
                }
                else {
                    max = lavy < i ? lavy : pravy;
                }
                if (vzostupne) {
                    if (max < i && table.getItemAtIndex(max).getKey() > table.getItemAtIndex(aktualny).getKey()) {
                        table.swap(max, aktualny);
                        aktualny = max;
                        vymena = true;
                    }
                } else {
                    if (max < i && table.getItemAtIndex(max).getKey() < table.getItemAtIndex(aktualny).getKey()) {
                        table.swap(max, aktualny);
                        aktualny = max;
                        vymena = true;
                    }
                }
            } while (vymena);
        }
    }

    template<typename K, typename T, typename R>
    void HeapSort<K, T, R>::sortWithCriterion(UnsortedSequenceTable<K, T> &table, bool vzostupne, CriterionObec<R>& criterion) {
        bool vymena = false;
        int aktualny;
        for (int i = 1; i <= table.size() - 1; i++)
        {
            aktualny = i;
            do {
                vymena = false;
                int otec = (aktualny - 1) / 2;

                if (vzostupne) {
                    if (aktualny > 0 && criterion.evaluate(*table.getItemAtIndex(aktualny).accessData()) >
                                        criterion.evaluate(*table.getItemAtIndex(otec).accessData())) {
                        table.swap(aktualny, otec);
                        aktualny = otec;
                        vymena = true;
                    }
                }
                else {
                    if (aktualny > 0 && criterion.evaluate(*table.getItemAtIndex(aktualny).accessData()) <
                                        criterion.evaluate(*table.getItemAtIndex(otec).accessData())) {
                        table.swap(aktualny,otec);
                        aktualny = otec;
                        vymena = true;
                    }
                }
            }
            while (vymena);
        }
        int max;
        for (int i = table.size() - 1; i >= 1; i--)
        {
            table.swap(0, i);
            aktualny = 0;
            do {
                vymena = false;
                int lavy = aktualny * 2 + 1;
                int pravy = aktualny * 2 + 2;
                if (lavy < i && pravy < i) {
                    if (vzostupne) {
                        max = criterion.evaluate(*table.getItemAtIndex(lavy).accessData()) >
                              criterion.evaluate(*table.getItemAtIndex(pravy).accessData()) ? lavy : pravy;
                    } else {
                        max = criterion.evaluate(*table.getItemAtIndex(lavy).accessData()) <
                              criterion.evaluate(*table.getItemAtIndex(pravy).accessData()) ? lavy : pravy;
                    }
                } else {
                    max = lavy < i ? lavy : pravy;
                }

                if (vzostupne) {
                    if (max < i && criterion.evaluate(*table.getItemAtIndex(max).accessData()) >
                                   criterion.evaluate(*table.getItemAtIndex(aktualny).accessData())) {
                        table.swap(max, aktualny);
                        aktualny = max;
                        vymena = true;
                    }
                } else {
                    if (max < i && criterion.evaluate(*table.getItemAtIndex(max).accessData()) <
                                        criterion.evaluate(*table.getItemAtIndex(aktualny).accessData())) {
                        table.swap(max, aktualny);
                        aktualny = max;
                        vymena = true;
                    }
                }
            }
             while (vymena);
        }
    }
}




