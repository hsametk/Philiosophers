/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:52:38 by hakotu            #+#    #+#             */
/*   Updated: 2025/05/23 17:59:07 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
    t_program program;

    if (check_input(argc, argv) != 0)
        return (1);

    memset(&program, 0, sizeof(t_program));
    program.num_of_philos = ft_atol(argv[1]);
    program.start_time = get_time();
    program.time_to_die = ft_atol(argv[2]);
    program.time_to_eat = ft_atol(argv[3]);
    program.time_to_sleep = ft_atol(argv[4]);
    if (argc == 6)
        program.num_times_to_eat = ft_atol(argv[5]);
    else
        program.num_times_to_eat = -1;

    program.philos = malloc(sizeof(t_philo) * program.num_of_philos);
    program.forks = malloc(sizeof(pthread_mutex_t) * program.num_of_philos);
    if (!program.philos || !program.forks)
    {
        printf("Error: Memory allocation failed.\n");
        return (1);
    }

    init_mutexes(&program);
    init_philos(&program);
    create_threads(&program);
    // if (program.num_of_philos == 1)
    // {
    //     handle_single_philo(&program);
    //     free(program.philos);
    //     free(program.forks);
    //     return (0);
    // }
    destroy_mutexes(&program);
    free(program.philos);
    free(program.forks);
    return (0);
}

int check_input(int argc, char *argv[])
{
    if (argv[1] == NULL)
    {
        printf("Error: No arguments provided.\n");
        return (1);
    }
    if (check_arg(argc, argv) != 0)
        return (1);

    if (ft_atol(argv[1]) < 1 || ft_atol(argv[1]) > 200)
    {
        printf("Error: Number of philosophers must be between 1 and 200.\n");
        return (1);
    }
    return (0);  // Eksik return değeri eklendi
}
/*
# Philosopher Projesi Roadmap

## 1. **Filozofların Rutinlerini Tamamlama**
   - **Düşünme (Thinking):**
     - Filozofun düşünme durumunu yazdır.
     - Çatal almadan önce düşünme süresi ekle.
   - **Çatal Alma (Taking Forks):**
     - Çift ve tek ID'li filozoflar için farklı çatal alma sırası belirle.
     - Mutex'leri kullanarak çatalları kilitle.
   - **Yemek Yeme (Eating):**
     - Yemek yeme süresini hesapla ve yazdır.
     - `last_meal` zamanını güncelle.
     - Yemek sayısını artır.
   - **Uyuma (Sleeping):**
     - Uyuma süresini hesapla ve yazdır.
     - Uyuma süresi boyunca bekle.
   - **Ölüm Kontrolü (Death Check):**
     - `dead_flag` kontrolü yaparak döngüyü sonlandır.

---

## 2. **Monitor Thread Eklemek**
   - **Ölüm Kontrolü:**
     - Her filozofun `last_meal` zamanını kontrol et.
     - Eğer bir filozofun `time_to_die` süresi dolmuşsa, ölüm durumunu yazdır ve programı sonlandır.
   - **Yemek Sayısı Kontrolü:**
     - Eğer tüm filozoflar belirli bir sayıda yemek yemişse, programı sonlandır.

---

## 3. **Deadlock Önleme**
   - **Çatal Alma Sırası:**
     - Çift ID'li filozoflar önce sağ çatalı, sonra sol çatalı almalı.
     - Tek ID'li filozoflar önce sol çatalı, sonra sağ çatalı almalı.
   - **Bekleme Süresi:**
     - Çatal alma sırasında küçük bir gecikme (`usleep`) ekle.
   - **Mutex Kullanımı:**
     - Çatallar için mutex'leri doğru sırada kilitle ve serbest bırak.

---

## 4. **Mutex ve Bellek Yönetimi**
   - **Mutex Destroy:**
     - Program sonunda tüm mutex'leri destroy et.
   - **Bellek Temizliği:**
     - `malloc` ile ayrılan bellekleri program sonunda serbest bırak.
   - **Hata Yönetimi:**
     - Mutex ve thread işlemlerinde hata kontrolü yap.
     - Hata durumunda kaynakları temizle ve programı sonlandır.

---

## 5. **Performans Optimizasyonu**
   - **Zaman Yönetimi:**
     - `get_time` fonksiyonunu optimize et.
     - `usleep` kullanımıyla CPU kullanımını azalt.
   - **Thread Senkronizasyonu:**
     - Gereksiz mutex kilitlemelerini kaldır.
     - Mutex kilitleme sırasını optimize et.

---

## 6. **Test ve Debug**
   - **Farklı Argüman Kombinasyonları:**
     - Farklı filozof sayıları ve zaman değerleriyle test yap.
   - **Deadlock Testi:**
     - Deadlock oluşup oluşmadığını kontrol et.
   - **Race Condition Testi:**
     - Aynı anda birden fazla thread'in aynı kaynağa erişip erişmediğini kontrol et.
   - **Bellek Sızıntısı Testi:**
     - `valgrind` veya benzeri araçlarla bellek sızıntılarını kontrol et.

---

## 7. **Dokümantasyon**
   - **README Dosyası:**
     - Projenin nasıl çalıştığını ve nasıl derleneceğini açıklayan bir README yaz.
   - **Kod Yorumları:**
     - Her fonksiyonun ne yaptığını açıklayan yorumlar ekle.
   - **Test Senaryoları:**
     - Kullanılan test senaryolarını dokümante et.

---

## 8. **Son Kontroller**
   - **Norminette Kontrolü:**
     - Kodunuzu 42 Norm kurallarına uygun hale getirin.
   - **Performans Testi:**
     - Büyük filozof sayılarıyla (örneğin 200) performansı test edin.
   - **Son Hata Kontrolleri:**
     - Tüm edge case'leri test edin ve hataları düzeltin.

Bu roadmap'i takip ederek projenizi adım adım tamamlayabilirsiniz.
*/

void destroy_mutexes(t_program *program)
{
    int i;

    for (i = 0; i < program->num_of_philos; i++)
        pthread_mutex_destroy(&program->forks[i]);
    pthread_mutex_destroy(&program->write_lock);
    pthread_mutex_destroy(&program->dead_lock);
}

// void handle_single_philo(t_program *program)
// {
//     printf("%zu 1 is thinking\n", get_time() - program->start_time);
//     printf("%zu 1 has taken a fork\n", get_time() - program->start_time);
//     usleep(program->time_to_die * 1000);
//     printf("%zu 1 died\n", get_time() - program->start_time);
// }