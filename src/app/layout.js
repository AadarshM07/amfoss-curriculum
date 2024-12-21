import "./globals.css";
import Link from "next/link";



function Headere() {
  return (
    <header className="bg-white">
      <div className="mx-auto max-w-screen-xl px-4 sm:px-6 lg:px-8">
        <div className="flex h-16 items-center justify-between">
          <div className="flex-1 md:flex md:items-center md:gap-12">
            <p className="text-rose-950 font-bold text-2xl">Winter</p>
          </div>

          <div className="md:flex md:items-center md:gap-12">
            <nav aria-label="Global" className="hidden md:block">
              <ul className="flex items-center gap-6 text-sm">
                <li>
                  <Link className="text-black transition hover:text-gray-500/75 text-2xl" href="."> Home </Link>
                </li>

                <li>
                  <Link className="text-black transition hover:text-gray-500/75 text-2xl" href="./movies"> Movies </Link>
                </li>

                <li>
                  <Link className="text-black transition hover:text-gray-500/75 text-2xl" href="#"> Top imdb </Link>
                </li>
              </ul>
            </nav>
          </div>
        </div>
      </div>
    </header>
  );
}

function Footere() {
  return (
    <footer className="bg-gray-50">
      <div className="mx-auto max-w-screen-xl px-4 py-8 sm:px-6 lg:px-8">
        <div className="sm:flex sm:items-center sm:justify-between">
          <div className="flex justify-center text-teal-600 sm:justify-start">
            <p className="text-rose-950 font-bold text-2xl">Aadarsh_M07</p>
          </div>

          <p className="mt-4 text-center text-sm text-gray-500 lg:mt-0 lg:text-right">
            Copyright &copy; 2024. All rights reserved.
          </p>
        </div>
      </div>
    </footer>
  );
}

export default function Heading({children}) {
  return (
    <html lang="en">
      <body className="h-screen flex flex-col justify-between bg-slate-900">
        <Headere />

        {children}

        <Footere />
      </body>
    </html>
  );
}

export {Headere,Footere};
