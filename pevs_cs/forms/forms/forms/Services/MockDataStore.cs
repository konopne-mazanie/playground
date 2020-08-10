using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using forms.Models;

namespace forms.Services
{
    public class MockDataStore : IDataStore<User>
    {
        List<User> users;
        private User me;

        public MockDataStore()
        {
            me = new User { Id = Guid.NewGuid().ToString(), Name = "Marian Kocner", Description = "Vykonny riaditel Transparency International", Icon = "https://picsum.photos/300?random=5" };
            users = new List<User>();
            var mockItems = new List<User>
            {
                new User { Id = Guid.NewGuid().ToString(), Name = "Robert Fico", Description="Premier", Icon="https://picsum.photos/300?random=1" },
                new User { Id = Guid.NewGuid().ToString(), Name = "Robert Kalinak", Description="Minister vnutra", Icon="https://picsum.photos/300?random=2" },
                new User { Id = Guid.NewGuid().ToString(), Name = "Lubos Blaha", Description="Predseda vyboru pre ludske prava", Icon="https://picsum.photos/300?random=3" },
                new User { Id = Guid.NewGuid().ToString(), Name = "Monika Jankovska", Description="Spojka MK", Icon="https://picsum.photos/300?random=4" }
            };

            foreach (var item in mockItems)
            {
                users.Add(item);
            }
        }
        public User getMe()
        {
            return me;
        }
        public async Task<User> GetItemAsync(string id)
        {
            return await Task.FromResult(users.FirstOrDefault(s => s.Id == id));
        }

        public async Task<IEnumerable<User>> GetItemsAsync(bool forceRefresh = false)
        {
            return await Task.FromResult(users);
        }
    }
}