using LedProject.Core.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using System.Data.Entity;
namespace LedProject.Web.Api.Controllers
{
    public class DataController : ApiController
    {
        public bool Get(string key)
        {
            using (var db = new MyDB())
            {
                var device = db.Devices.Where(x => x.Key == key).FirstOrDefault();
                return device.IsOpen;
            }
        }
    }

}
