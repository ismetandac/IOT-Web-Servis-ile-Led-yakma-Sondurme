using LedProject.Core.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace LedProject.Web.UI.Controllers
{
    public class HomeController : Controller
    {
        // GET: Home
        public ActionResult Index()
        {

            return View();
        }
        [HttpPost]
        public ActionResult Index(int id = 0)
        {
            using (var db = new MyDB())
            {
                var device = db.Devices.Where(x => x.ID == 1).FirstOrDefault();
                device.IsOpen = device.IsOpen == true ? false : true;
                db.SaveChanges();
            }
            return View();
        }


    }
}