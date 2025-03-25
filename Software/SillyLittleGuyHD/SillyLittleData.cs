using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GMap.NET;

namespace SillyLittleGuyHD
{
    internal class SillyLittleData
    {
        #region members

        public List<PointLatLng> locations { get; set; }
        
        private string _uid;
        public string uid
        {
            get
            {
                return _uid;
            }
            set
            {
                _uid = value;
            }
        }

        private string _password;
        public string password
        {
            get
            {
                return _password;
            }
            set
            {
                _password = value;
            }
        }

        private int _dailysteps;
        public int dailySteps
        {
            get
            {
                return _dailysteps;
            }
            set
            {
                _dailysteps = value;
            }
        }

        private int _weeklysteps;
        public int WeeklySteps
        {
            get
            {
                return _weeklysteps;
            }
            set
            {
                _weeklysteps = value;
            }
        }

        private int _lifesteps;
        public int lifeSteps
        {
            get
            {
                return _lifesteps;
            }
            set
            {
                _lifesteps = value;
            }
        }

        private int _friendship;
        public int friendship
        {
            get
            {
                return _friendship;
            }
            set
            {
                _friendship = value;
            }
        }

        private int _difficulty;
        public int difficilty
        {
            get
            {
                return _difficulty;
            }
            set
            {
                _difficulty = value;
            }
        }

        private int _evolution;
        public int evolution
        {
            get
            {
                return _evolution;
            }
            set
            {
                _evolution = value;
            }
        }

        #endregion

        public SillyLittleData(string id, string pass, int daily, int weekly, int lifetime, int friend, int diff, int evo)
        {
            uid = id;
            password = pass;
            dailySteps = daily;
            WeeklySteps = weekly;
            lifeSteps = lifetime;
            friendship = friend;
            difficilty = diff;
            evolution = evo;
        }

        public override string ToString()
        {
            return $"(uid:),(),()";
        }

        public Dictionary<string, string> GetDictionary()
        {
            return new Dictionary<string, string> { { "uid", uid }, { "password", password }, { "dailySteps", dailySteps.ToString() }, { "weeklySteps", WeeklySteps.ToString() }, { "lifeSteps", lifeSteps.ToString() }, { "friendship", friendship.ToString() }, { "difficulyty", difficilty.ToString() }, { "evolution", evolution.ToString() } };
        }

        public string GetId()
        {
            return $"uid='{uid}'";
        }
    }
}
