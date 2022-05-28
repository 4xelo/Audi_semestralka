#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"

namespace structures
{

	/// <summary> Triedenie Shell sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class ShellSort : public Sort<K, T>
	{
        void shell(int krok, UnsortedSequenceTable<K, T>& table);
	public:
		/// <summary> Utriedi tabulku triedenim Shell sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
	};

    template<typename K, typename T>
    inline void ShellSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
    {
        int krok = log10(table.size());
        shell(krok, table);
    }

    template<typename K, typename T>
    inline void ShellSort<K, T>::shell(int krok, UnsortedSequenceTable<K, T>& table) {
        for(int delta = 0; delta < krok; delta++) {
            for (int i = delta; i < table.size(); i += krok) {
                int j = i;
                while ((j-krok >= delta) && (table.getItemAtIndex(j).getKey() < table.getItemAtIndex(j - krok).getKey())) {
                    Utils::swap(table.getItemAtIndex(j), table.getItemAtIndex(j-krok));
                    j -= krok;
                }
            }
        }
        if (krok > 1)
            shell(krok-1, table);
    }
}