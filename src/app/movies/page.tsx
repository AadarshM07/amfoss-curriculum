import "../globals.css";
import Link from "next/link";
import moviesdata from "../moviedata";

export default function Movies() {
  return (
    <div className=" mx-10 my-10 flex flex-row flex-wrap gap-12">

      {moviesdata.map((movie) => (
        <article
          className="relative overflow-hidden rounded-lg transition hover:shadow-[0_0_15px_5px_rgba(255,255,255,0.8)] w-1/6"
        >
          <img
            alt={movie.name}
            src={movie.imageUrl}
            className="absolute inset-0 h-full w-full object-cover"
          />

          <div className="relative bg-gradient-to-t from-gray-900/50 to-gray-900/25 pt-32 sm:pt-48 lg:pt-64">
            <div className="p-4 sm:p-6">
              <time className="block text-xs text-white/90">{movie.releaseDate}</time>

              <a href="#">
                <h3 className="mt-0.5 text-lg text-white">{movie.name}</h3>
              </a>

              <p className="mt-2 line-clamp-3 text-sm/relaxed text-white/95">
                {movie.smallDescription}
              </p>
            </div>
          </div>
        </article>
      ))}
    </div>
  );
}