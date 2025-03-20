using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SillyLittleGuyHD
{
    internal class SillyLittleData
    {
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



        public SillyLittleData()
        {

        }
    }
}
