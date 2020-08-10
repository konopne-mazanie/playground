using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace forms.Services
{
    public interface IDataStore<T>
    {
        T getMe();
        Task<T> GetItemAsync(string id);
        Task<IEnumerable<T>> GetItemsAsync(bool forceRefresh = false);
    }
}
