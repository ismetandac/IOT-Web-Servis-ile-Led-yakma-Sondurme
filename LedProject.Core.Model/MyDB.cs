using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LedProject.Core.Model
{
    public class MyDB : DbContext
    {
        public MyDB():base()
        {

        }
        public DbSet<Device> Devices { get; set; }


    }
}
